# make sure to check the lens first with bin/view

# store passed variables
args=("$@")
LENS_ID=${args[0]}
LENS_FOCAL_LENGTH=${args[1]}
MAX_DEGREE=${args[2]} #default = 11
MAX_COEFFICIENTS=${args[3]} #default = 28

printf "database->code conversion:\n"
printf "\t lens id: %s\n" $LENS_ID
printf "\t focal length: %s\n" $LENS_FOCAL_LENGTH

# generate lens name from database id
read LENS_NAME <<< $($LENTIL_PATH/bin/print-lens-path $LENS_ID) &&
printf "\t lens name: %s\n" $LENS_NAME
printf "%s\n" "-------------------------------------"

# calculate fstop and add it to the database
# special 0 case first, which takes unscaled lens data to calculate the fstop
$LENTIL_PATH/bin/calculate-fstop $LENS_ID 0 &&
$LENTIL_PATH/bin/calculate-fstop $LENS_ID $LENS_FOCAL_LENGTH &&

# add raytraced focal length
$LENTIL_PATH/bin/calculate-focal-length $LENS_ID &&

# generate empty polynomial
mkdir -p -v $LENTIL_PATH/data/tmp/$LENS_ID/$LENS_FOCAL_LENGTH/ &&
$LENTIL_PATH/bin/genpoly $MAX_DEGREE $LENTIL_PATH/data/tmp/$LENS_ID/$LENS_FOCAL_LENGTH/sorted.poly &&

# compute polynomials
mkdir -p -v $LENTIL_PATH/database/lenses/$LENS_NAME/$LENS_FOCAL_LENGTH/fitted/ &&
$LENTIL_PATH/bin/fit $LENS_ID $LENS_FOCAL_LENGTH $MAX_DEGREE $MAX_COEFFICIENTS $LENTIL_PATH/data/tmp/$LENS_ID/$LENS_FOCAL_LENGTH/sorted.poly &&

# generate code from .fit files
mkdir -p -v $LENTIL_PATH/database/lenses/$LENS_NAME/$LENS_FOCAL_LENGTH/code/ &&
$LENTIL_PATH/bin/gencode $LENS_ID $LENS_FOCAL_LENGTH &&

# add fitted focal length to json database
$LENTIL_PATH/bin/add-fitted-focal-length $LENS_ID $LENS_FOCAL_LENGTH &&
printf "Added %s to list of fitted focal lengths." $LENS_FOCAL_LENGTH &&

# auto-generate lens defines
$LENTIL_PATH/bin/generate-lens-defines &&

$LENTIL_PATH/bin/create-public-json &&
python $LENTIL_PATH/src/copy-images-to-www.py &&

# cleanup
rm -rf -v $LENTIL_PATH/data/tmp/$LENS_ID/$LENS_FOCAL_LENGTH &&
# rm -d -v $LENTIL_PATH/data/tmp/$LENS_ID

# build pota with new lens
cd $LENTIL_PATH/../pota/build/local/ &&
. ./build_local.sh &&

# render unit tests
python $LENTIL_PATH/src/unit_render_arnold.py $LENS_ID $LENS_FOCAL_LENGTH


# needs to be flagged production-ready after tests