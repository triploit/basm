func install
{
  cd ..
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
