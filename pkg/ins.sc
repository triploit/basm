name basm
user triploit
ver 0.1.7.0
dep triploit basm-lib 0.0.0.1

func install {
  g++ main.cpp -o basm -w -static -std=c++11
  chmod +x basm
  sudo mv basm /usr/bin/basm

  echo -e "\e[1;32m## Install BASM Library..."
  sudo secpm install triploit:basm-lib
  echo -e "\e[1;32m## Finished."
}

func update {
  g++ main.cpp -o basm -w -static -std=c++11
  chmod +x basm
  sudo mv basm /usr/bin/basm
}

func remove {
  sudo rm /usr/bin/basm
}

func werror {
  @echo There is no Windows-Support yet.
  @echo Install this package manually.
}

func install_win {
  &werror
}

func remove_win {
  &werror
}

func update_win {
  &werror
}
