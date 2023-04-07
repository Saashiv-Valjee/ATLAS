echo "INFO: sourcing /srv/my_release_setup.sh inside the container. This should not run if it is a ATLAS standalone container"
retCode=$?
date +"%H:%M:%S %Y/%m/%d"
if [ $? -ne 0 ]; then
    retCode=$?
fi
return $retCode