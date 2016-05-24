#Instructions
#move the "rix" file to the rix folder
#move this file to the rix folder
#execute this command inside of the rix folder:
#   $. paths.sh

RIX_PATH=$(pwd)
export  RIX_HOME=${RIX_PATH}
sudo ln -s "$RIX_HOME/rix" /usr/bin/
