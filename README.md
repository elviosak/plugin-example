# Example plugin for [lxqt-panel](https://github.com/lxqt/lxqt-panel)

Instructions:

```bash
#clone repo
git clone https://github.com/elviosak/plugin-example.git ./plugin-newname

# cd into folder
cd plugin-newname

# run rename script
chmod +x ./renameplugin.sh
./renameplugin.sh Example NewName

# install
chmod +x ./install.sh
./install.sh
```
If everything was  succesful you should have a new plugin ready to be added to your panel, named `NewName`.

When testing changes you will probably need to restart panel, e.g.

```bash
killall lxqt-panel && lxqt-panel &
```





