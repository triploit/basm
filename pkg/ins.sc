func install
{
  g++ main.cpp -o basm -w -static
  chmod +x basm
  sudo mv basm /usr/bin/basm

  # echo -e "\e[1;32m## Install BASM Library..."
  sudo secpm install basm-lib
  # echo -e "\e[1;32m## Finished."
}

func update
{
  &install
}

func remove
{
  sudo rm /usr/bin/basm
}

func werror
{
  @echo There is no Windows-Support yet.
  @echo Install this package manually.
}

func install_win
{
  &werror
}

func remove_win
{
  &werror
}

func update_win
{
  &werror
}
