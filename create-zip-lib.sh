#create zip lib
cd ..
find RoboCar/ -path '*/.*' -prune -o -type f \( -iname "*.*" ! -iname "*.sh" \) -print | zip RoboCar.zip -@
cp RoboCar.zip RoboCar
cd RoboCar
