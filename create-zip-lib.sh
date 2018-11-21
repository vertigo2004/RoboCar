#create zip lib
rm RoboCar.zip
cd ..
find RoboCar/ -path '*/.*' -prune -o -type f \( -iname "*.*" ! -iname "*.sh" ! -iname "*.zip" \) -print | zip RoboCar.zip -@
mv RoboCar.zip RoboCar
cd RoboCar
