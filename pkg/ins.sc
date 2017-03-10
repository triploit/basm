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

func install_win
{
  echo Ich bin auf Windows!
  [
    echo Hallo!
  ]
}
