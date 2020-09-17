# Kitchen Monitoring System

## Overview

This directory will contain all of the code necessary to run a kitchen wide system to have a real time up to date count on consumables. The database will store every item types quantity, expiration, nutritional facts, and location. This will be accomplished by having an openCV based system 'watching' entry points at food storage locations such as the pantry or fridge. Should the image contain a "Nutrition Fact" label, information will be pulled from that and stored along side the food item in the database. For foods which do not include such labels, such as raw veggies, fruits, meat, and fish, shall be attempted to be recognized with Object Detection and have data pulled from a separate database. Otherwise, nutritional data and shelf life will need to be imputed manually.

Additionally, this system will keep track of non-perishable things like cooking/eating utensils.

## Recommender System

The Recommender System (to be dubbed "Red Ball" after the red balls from minority report which would predict when a murder was about to occur) will take food already in the house and find recipes which can utilize them.
