# make sure to check the lens first with bin/view

# pass multiple focal lengths, evaluate them parallel
# [[id1, fl1, fl2, fl3, fl4, fl5], [id2, fl1, fl2, fl3, fl4]]
# will need more descriptive printf outputs to differentiate

# store passed variables
args=("$@")
LENS_ID=${args[0]}
LENS_FOCAL_LENGTH=${args[1]}
MAX_DEGREE=${args[2]} #default = 11
MAX_COEFFICIENTS=${args[3]} #default = 28


echo "LENS ID: " $LENS_ID
echo "FOCAL LENGTH: " $LENS_FOCAL_LENGTH

# generate lens name from database id
read LENS_NAME <<< $($LENTIL_PATH/bin/print-lens-path $LENS_ID $LENS_FOCAL_LENGTH $i) &&
echo "LENS_NAME: " $LENS_NAME &&

# calculate fstop and add it to the database
$LENTIL_PATH/bin/calculate-fstop $LENS_ID &&

# add raytraced focal length and fstop
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
echo "Added " $LENS_FOCAL_LENGTH " to list of fitted focal lengths." &&

# needs to be flagged production-ready after tests

# auto-generate lens defines
$LENTIL_PATH/bin/generate-lens-defines &&

$LENTIL_PATH/bin/create-public-json &&
python $LENTIL_PATH/src/copy-images-to-www.py &&

# cleanup
rm -rf -v $LENTIL_PATH/data/tmp/$LENS_ID/$LENS_FOCAL_LENGTH &&
rm -d -v $LENTIL_PATH/data/tmp/$LENS_ID