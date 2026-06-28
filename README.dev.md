[![Build QMK firmware](https://github.com/zunoffon/qmk_userspace/actions/workflows/build_binaries.yaml/badge.svg?branch=main)](https://github.com/zunoffon/qmk_userspace/actions/workflows/build_binaries.yaml)
# Setup
## Prepare Repositories
Before setting up build environment, create a workspace directory and clone the required repositories.
```bash
git clone --recurse-submodules git@github.com:zunoffon/qmk_userspace.git
```
## Prepare Your Build Environment
### linux
```bash
curl -fsSL https://install.qmk.fm | sh
```
### windows
Install https://msys.qmk.fm/
```bash
C:/QMK_MSYS/shell_connector.cmd
```
## Run QMK Setup
```bash
cd qmk_userspace
qmk setup -H  ./qmk_firmware
qmk config user.qmk_home="$(realpath qmk_firmware)"
qmk config user.overlay_dir="$(realpath .)"
```
## Building & Flashing Firmware
### Corne V4 Pro Micro Edition ([Repo](https://github.com/klouderone/cornev4promicroedition))
```bash
qmk compile -j$(nproc) -kb crkbd/rev1 -km miryoku -e CONVERT_TO=rp2040_ce
# Debugging
qmk compile -j$(nproc) -kb crkbd/rev1 -km miryoku -e CONVERT_TO=rp2040_ce -e CONSOLE_ENABLE=yes
qmk flash   -j$(nproc) -kb crkbd/rev1 -km miryoku -e CONVERT_TO=rp2040_ce -bl uf2
```
# 📌 Maintenance Note
## Manage upstream QMK
According to the official [qmk_userspace documentation](https://github.com/qmk/qmk_userspace/blob/main/README.md):<br>
> If you wish to manually manage `qmk_firmware` using git within the userspace repository, you can add `qmk_firmware` as a submodule in the userspace directory instead. GitHub Actions will automatically use the submodule at the pinned revision if it exists, otherwise it will use the default latest revision of `qmk_firmware` from the main repository.
```bash
# Navigate to the submodule and check out a specific release tag
cd qmk_firmware
git checkout <revision> --recurse-submodules
cd ..
# For local build, point your local QMK CLI to the pinned submodule directory
qmk setup -H  ./qmk_firmware
# (Optional) Track the pinned version in your userspace repository
git add qmk_firmware
git commit -m "qmk_firmware : bump to <revision>"
```
## Downstream miryoku
Following [breaking changes](https://github.com/manna-harbour/miryoku/discussions/287) in QMK that introduced the new External Userspace format,
the original implementation at manna-harbour/miryoku_qmk is no longer actively maintained.
[This repository](https://github.com/manna-harbour/miryoku_qmk/tree/miryoku/users/manna-harbour_miryoku) forks and updates that configuration into `qmk_userspace/users/miryoku`
## Adding New Modules
```bash
cd qmk_userspace
git submodule add https://github.com/getreuer/qmk-modules.git modules/getreuer
```
## GitHub Actions:
Adding new build release target
```bash
qmk userspace-add -kb crkbd/rev1 -km miryoku -e CONVERT_TO=rp2040_ce
qmk userspace-doctor
```
