set -euo pipefail

# Count lines in a repo with extras:
# - per-file line counts (optional)
# - totals by extension
# - top-N largest files
# - excludes dirs
# - can limit to certain extensions
#
# Examples:
#   ./count_lines.sh
#   ./count_lines.sh --ext cpp,hpp,c,h
#   ./count_lines.sh --exclude build,.git,third_party --top 30
#   ./count_lines.sh --paths src include --no-per-file

TOP_N=20
SHOW_PER_FILE=1
EXT_FILTER=""            # comma-separated, e.g. "cpp,hpp,c,h"
EXCLUDE_DIRS=".git,build,bin,out,.vs,.idea,.vscode,cmake-build-debug,cmake-build-release"
PATHS=()

usage() {
  cat <<'EOF'
Usage: ./count_lines.sh [options]

Options:
  --top N                 Show top-N largest files (default: 20)
  --no-per-file           Do not print per-file line counts
  --per-file              Print per-file line counts (default)
  --ext a,b,c             Only include these extensions (no dots), e.g. cpp,hpp,c,h
  --exclude d1,d2         Exclude directories (default: .git,build,bin,out,...)
  --paths p1 p2 ...       Only count files under these paths (must be last option group)
  -h, --help              Show help

Notes:
  - If inside a git repo, counts only tracked files (git ls-files).
  - Skips binary files (uses grep -Iq).
EOF
}

# --- parse args ---
while [[ $# -gt 0 ]]; do
  case "$1" in
    --top) TOP_N="${2:-}"; shift 2;;
    --no-per-file) SHOW_PER_FILE=0; shift;;
    --per-file) SHOW_PER_FILE=1; shift;;
    --ext) EXT_FILTER="${2:-}"; shift 2;;
    --exclude) EXCLUDE_DIRS="${2:-}"; shift 2;;
    --paths)
      shift
      PATHS=("$@")
      break
      ;;
    -h|--help) usage; exit 0;;
    *) echo "Unknown option: $1" >&2; usage; exit 2;;
  esac
done

# --- build exclude regex ---
# match any excluded directory segment: /(dir)/ or ^dir/
IFS=',' read -r -a excl_arr <<< "$EXCLUDE_DIRS"
excl_regex=""
for d in "${excl_arr[@]}"; do
  [[ -z "$d" ]] && continue
  d_esc=$(printf '%s' "$d" | sed 's/[.[\*^$()+?{|]/\\&/g')
  if [[ -z "$excl_regex" ]]; then
    excl_regex="(^|/)$d_esc(/|$)"
  else
    excl_regex="$excl_regex|(^|/)$d_esc(/|$)"
  fi
done

# --- extension filter set ---
declare -A ext_ok=()
if [[ -n "$EXT_FILTER" ]]; then
  IFS=',' read -r -a exts <<< "$EXT_FILTER"
  for e in "${exts[@]}"; do
    e="${e#.}"  # strip dot if user included
    [[ -n "$e" ]] && ext_ok["$e"]=1
  done
fi

# --- get file list ---
files=()
if git rev-parse --is-inside-work-tree >/dev/null 2>&1; then
  if ((${#PATHS[@]} == 0)); then
    mapfile -t files < <(git ls-files)
  else
    mapfile -t files < <(git ls-files -- "${PATHS[@]}")
  fi
else
  # fallback: not a git repo
  if ((${#PATHS[@]} == 0)); then
    mapfile -t files < <(find . -type f)
  else
    mapfile -t files < <(find "${PATHS[@]}" -type f)
  fi
fi

# --- collect stats ---
total=0
declare -A by_ext=()
# store "lines<TAB>path" for sorting top-N
tmp_list=()

for f in "${files[@]}"; do
  [[ -f "$f" ]] || continue

  # exclude directories
  if [[ -n "$excl_regex" ]] && [[ "$f" =~ $excl_regex ]]; then
    continue
  fi

  # extension filter (no extension => skip if filter active)
  ext="${f##*.}"
  if [[ "$f" == "$ext" ]]; then
    ext="" # no dot in name
  fi
  if [[ -n "$EXT_FILTER" ]]; then
    [[ -n "$ext" && -n "${ext_ok[$ext]:-}" ]] || continue
  fi

  # skip binary files
  if ! grep -Iq . "$f" 2>/dev/null; then
    continue
  fi

  n=$(wc -l < "$f" | tr -d ' ')
  total=$((total + n))

  k="${ext:-<noext>}"
  by_ext["$k"]=$(( ${by_ext["$k"]:-0} + n ))

  tmp_list+=("${n}"$'\t'"${f}")

  if (( SHOW_PER_FILE == 1 )); then
    printf "%8d  %s\n" "$n" "$f"
  fi
done

# --- totals by extension ---
echo
echo "Totals by extension:"
# print sorted by lines desc
for k in "${!by_ext[@]}"; do
  printf "%s\t%d\n" "$k" "${by_ext[$k]}"
done | sort -t $'\t' -k2,2nr | while IFS=$'\t' read -r k v; do
  printf "%10s  %d\n" "$k" "$v"
done

# --- top-N files ---
echo
echo "Top ${TOP_N} files:"
printf "%s\n" "${tmp_list[@]}" | sort -t $'\t' -k1,1nr | head -n "$TOP_N" | while IFS=$'\t' read -r n p; do
  printf "%8d  %s\n" "$n" "$p"
done

echo
echo "TOTAL: $total lines"
