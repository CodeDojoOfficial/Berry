function berry() {
  if [[ ${BERRY_HOME} != "" ]]; then
    ${BERRY_HOME}/BDK/bin/compiler $@
  else
    echo "Your BERRY_HOME environment variable does not exist."
    return 1
  fi
}
