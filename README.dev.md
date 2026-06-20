# Setup
## Prepare Repositories
Before setting up build environment, create a workspace directory and clone the required repositories.
```bash
git clone --branch 0.33.7 git@github.com:qmk/qmk_firmware.git
git clone git@github.com:zunoffon/qmk_userspace.git
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
qmk setup -H  ./qmk_firmware
qmk config user.qmk_home="$(realpath qmk_firmware)"
qmk config user.overlay_dir="$(realpath qmk_userspace)"
```
# 📌 Maintenance Note
## Downstream miryoku
Following [breaking changes](https://github.com/manna-harbour/miryoku/discussions/287) in QMK that introduced the new External Userspace format,
the original implementation at manna-harbour/miryoku_qmk is no longer actively maintained.
[This repository](https://github.com/manna-harbour/miryoku_qmk/tree/miryoku/users/manna-harbour_miryoku) forks and updates that configuration into `qmk_userspace/users/manna-harbour_miryoku`
