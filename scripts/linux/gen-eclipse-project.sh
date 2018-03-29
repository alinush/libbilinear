set -e

sourcedir=$(cd $(dirname $0)/../..; pwd -P)
builddir="$LIBBILINEAR_BUILD_DIR/eclipse"

mkdir -p "$builddir"
cd "$builddir"
echo "Storing project in $builddir ..."
cmake $LIBBILINEAR_CMAKE_ARGS -G "Eclipse CDT4 - Unix Makefiles" "$sourcedir"
