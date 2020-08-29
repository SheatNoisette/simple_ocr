/*
** utils.c for OCR in src/commons
**
** Made by SheatNoisette
** Login   SheatNoisette
**
** Started on  2019 SheatNoisette
*/

/*  Useful functions that doesn't require their own files */

/*
** Max
** Return the biggest number between two values (val_1 and val_2)
*/

int max(int val_1, int val_2){

    if (val_1 > val_2)
        return val_1;
    
    return val_2;
}


/*
** Min
** Return the smallest number between two values (val_1 and val_2)
*/

int min(int val_1, int val_2){

    if (val_1 < val_2)
        return val_1;
    
    return val_2;
}

/*
** Max 3
** Return the biggest number between three values (val_1, val_2 and val_3)
*/

int max_3 (int val_1, int val_2, int val_3){

    return max(val_1, max(val_2, val_3));
}


/*
** Min 3
** Return the smallest number between three values (val_1, val_2 and val_3)
*/

int min_3 (int val_1, int val_2, int val_3){

    return min(val_1, min(val_2, val_3));
}

