# make sure to check the lens first with bin/view
# pass multiple focal lengths, evaluate them parallel


# store passed variables
args=("$@")
LENS_ID=${args[0]}
LENS_FOCAL_LENGTH=${args[1]}

echo "LENS ID: " $LENS_ID
echo "FOCAL LENGTH: " $LENS_FOCAL_LENGTH

# generate lens name from database
read LENS_NAME <<< $($LENTIL_PATH/bin/print-lens-path $LENS_ID $LENS_FOCAL_LENGTH $i)
echo "LENS_NAME: " $LENS_NAME

mkdir -p $LENTIL_PATH/data/tmp/$LENS_ID/$LENS_FOCAL_LENGTH/
$LENTIL_PATH/bin/genpoly 11 $LENTIL_PATH/data/tmp/$LENS_ID/$LENS_FOCAL_LENGTH/sorted.poly

# need to create the directories
mkdir -p $LENTIL_PATH/database/lenses/$LENS_NAME/$LENS_FOCAL_LENGTH/fitted/
$LENTIL_PATH/bin/fit $LENS_ID $LENS_FOCAL_LENGTH 11 28 $LENTIL_PATH/data/tmp/$LENS_ID/$LENS_FOCAL_LENGTH/sorted.poly

mkdir -p $LENTIL_PATH/database/lenses/$LENS_NAME/$LENS_FOCAL_LENGTH/code/
$LENTIL_PATH/bin/gencode $LENS_ID $LENS_FOCAL_LENGTH

# add fitted focal length to json database

# cleanup
rm -rf -v $LENTIL_PATH/data/tmp/$LENS_ID/$LENS_FOCAL_LENGTH
rm -d -v $LENTIL_PATH/data/tmp/$LENS_ID