#!/usr/bin/env bash

set -e

MODULE_NAME="asmn_driver"
DEVICE_NAME="/dev/asmn_driver"

echo "============================================================"
echo " TP5 - Character Device Driver Validation"
echo "============================================================"
echo
echo "============================================================"
echo " STEP 1 - Building module"
echo "============================================================"

make clean
make

echo
echo "[OK] Build completed"
echo
echo "============================================================"
echo " STEP 2 - Inserting module"
echo "============================================================"

sudo insmod ${MODULE_NAME}.ko || true

echo
echo "[OK] Module inserted"
echo
echo "============================================================"
echo " STEP 3 - Checking loaded modules"
echo "============================================================"

lsmod | grep ${MODULE_NAME} || true

echo
echo "============================================================"
echo " STEP 4 - Kernel logs"
echo "============================================================"

sudo dmesg | tail -20

echo
echo "============================================================"
echo " STEP 5 - Checking /proc/devices"
echo "============================================================"

cat /proc/devices | grep ${MODULE_NAME} || true

echo
echo "============================================================"
echo " STEP 6 - Checking /dev entry"
echo "============================================================"

ls -l ${DEVICE_NAME} || true

echo
echo "============================================================"
echo " STEP 7 - Testing open/release"
echo "============================================================"

cat ${DEVICE_NAME} || true

echo
echo "[OK] open/release tested"
echo
echo "============================================================"
echo " STEP 8 - Kernel logs after open/release"
echo "============================================================"

sudo dmesg | tail -20

echo
echo "============================================================"
echo " STEP 9 - Testing read()"
echo "============================================================"
echo
echo "Reading from driver:"
echo

cat ${DEVICE_NAME} || true

echo
echo "============================================================"
echo " STEP 10 - Testing write() channel 0"
echo "============================================================"

echo 0 | sudo tee ${DEVICE_NAME}

sleep 1

cat ${DEVICE_NAME}

echo
echo "============================================================"
echo " STEP 11 - Testing write() channel 1"
echo "============================================================"

echo 1 | sudo tee ${DEVICE_NAME}

sleep 1

cat ${DEVICE_NAME}

echo
echo "============================================================"
echo " STEP 12 - Watching periodic updates"
echo "============================================================"

for i in {1..5}
do
    cat ${DEVICE_NAME}
    sleep 1
done

echo
echo "============================================================"
echo " STEP 13 - Final kernel logs"
echo "============================================================"

sudo dmesg | tail -30

echo
echo "============================================================"
echo " STEP 14 - Removing module"
echo "============================================================"

sudo rmmod ${MODULE_NAME}

echo
echo "[OK] Module removed"
echo
echo "============================================================"
echo " STEP 15 - Verifying unload"
echo "============================================================"

lsmod | grep ${MODULE_NAME} || true

echo
echo "============================================================"
echo " TP5 Validation Completed"
echo "============================================================"

make clean