func install
{
  g++ main.cpp -o basm -w -static
  chmod +x basm
  sudo mv basm /usr/bin/basm
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
