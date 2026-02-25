#!/usr/bin/env bash
# ==============================================================================
#  build.sh — STM32 CMake Build Automation Script
#  Usage: ./build.sh [option]
#
#  Options:
#    (none)       Configure (if needed) + build
#    clean        Wipe build/ and rebuild from scratch
#    flash        Build then flash via OpenOCD
#    size         Print memory usage of last build
#    help         Show this help message
# ==============================================================================

# ── Resolve script location (so paths work regardless of where you call from) ─
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# ── Config ────────────────────────────────────────────────────────────────────
BUILD_DIR="${SCRIPT_DIR}/PegasusBuild"  # Build output directory
BUILD_TYPE="Debug"          # Debug | Release | MinSizeRel | RelWithDebInfo
JOBS=$(nproc 2>/dev/null || sysctl -n hw.logicalcpu 2>/dev/null || echo 4)
# ─────────────────────────────────────────────────────────────────────────────

# Colors
RED='\033[0;31m'; GREEN='\033[0;32m'; YELLOW='\033[1;33m'
CYAN='\033[0;36m'; BOLD='\033[1m'; NC='\033[0m'

info()    { echo -e "${CYAN}[INFO]${NC}  $*"; }
success() { echo -e "${GREEN}[OK]${NC}    $*"; }
warn()    { echo -e "${YELLOW}[WARN]${NC}  $*"; }
error()   { echo -e "${RED}[ERROR]${NC} $*"; exit 1; }

# ── Helper: check required tools ─────────────────────────────────────────────
check_deps() {
    for tool in cmake arm-none-eabi-gcc arm-none-eabi-g++ arm-none-eabi-objcopy; do
        command -v "$tool" &>/dev/null || error "'$tool' not found. Is the ARM toolchain on your PATH?"
    done
}

# ── Configure (only if build dir doesn't exist or CMakeCache is missing) ─────
configure() {
    if [ ! -f "${BUILD_DIR}/CMakeCache.txt" ]; then
        info "Configuring project (BUILD_TYPE=${BUILD_TYPE})..."
        cmake -S "${SCRIPT_DIR}" -B "${BUILD_DIR}" \
              -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" \
              -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
        || error "CMake configuration failed."
        success "Configuration done."
    else
        info "Build directory exists — skipping configure. Run './build.sh clean' to reconfigure."
    fi
}

# ── Build ─────────────────────────────────────────────────────────────────────
build() {
    info "Building with ${JOBS} parallel jobs..."
    cmake --build "${BUILD_DIR}" --parallel "${JOBS}" \
    || error "Build failed. Check errors above."
    success "Build succeeded!"
}

# ── Clean ─────────────────────────────────────────────────────────────────────
clean() {
    warn "Removing '${BUILD_DIR}/' directory..."
    rm -rf "${BUILD_DIR}"
    success "Cleaned. Run './build.sh' to configure and rebuild."
}

# ── Flash ─────────────────────────────────────────────────────────────────────
flash() {
    command -v openocd &>/dev/null || error "OpenOCD not found. Install it or add it to PATH."
    build
    info "Flashing via OpenOCD..."
    cmake --build "${BUILD_DIR}" --target flash \
    || error "Flashing failed."
    success "Flashed successfully!"
}

# ── Size ──────────────────────────────────────────────────────────────────────
size() {
    [ -d "${BUILD_DIR}" ] || error "Build directory '${BUILD_DIR}' not found. Run './build.sh' first."
    ELF=$(find "${BUILD_DIR}" -name "*.elf" | head -n 1)
    [ -z "$ELF" ] && error "No .elf file found in '${BUILD_DIR}/'. Build first."
    info "Memory usage for: $(basename "$ELF")"
    arm-none-eabi-size --format=berkeley "$ELF"
}

# ── Help ──────────────────────────────────────────────────────────────────────
usage() {
    echo -e "
${BOLD}Usage:${NC} ./build.sh [option]

  ${GREEN}(none)${NC}    Configure if needed, then build
  ${GREEN}clean${NC}     Wipe build/ and do a fresh rebuild
  ${GREEN}flash${NC}     Build and flash via OpenOCD
  ${GREEN}size${NC}      Print memory usage of last build
  ${GREEN}help${NC}      Show this message

${BOLD}Config (edit inside build.sh):${NC}
  BUILD_DIR   = ${BUILD_DIR}
  BUILD_TYPE  = ${BUILD_TYPE}
  JOBS        = ${JOBS}
"
}

# ── Entry Point ───────────────────────────────────────────────────────────────
check_deps

case "${1:-build}" in
    build|"")   configure && build  ;;
    clean)      clean ;;
    flash)      configure && flash  ;;
    size)       size                ;;
    help|--help|-h) usage           ;;
    *) error "Unknown option '${1}'. Run './build.sh help' for usage." ;;
esac