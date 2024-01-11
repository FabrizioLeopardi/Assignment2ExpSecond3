#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/root/Desktop/my_ros_work/src/rosbot_description"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/root/Desktop/my_ros_work/install/lib/python3/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/root/Desktop/my_ros_work/install/lib/python3/dist-packages:/root/Desktop/my_ros_work/build/lib/python3/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/root/Desktop/my_ros_work/build" \
    "/usr/bin/python3" \
    "/root/Desktop/my_ros_work/src/rosbot_description/setup.py" \
     \
    build --build-base "/root/Desktop/my_ros_work/build/rosbot_description" \
    install \
    --root="${DESTDIR-/}" \
    --install-layout=deb --prefix="/root/Desktop/my_ros_work/install" --install-scripts="/root/Desktop/my_ros_work/install/bin"
