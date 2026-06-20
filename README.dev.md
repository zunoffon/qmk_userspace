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
