/*
 * @file t_swift_vector.h
 * @brief A Taylor Swift themed, threadsafe dynamically expanding array.
 *
 * Autocomplete is almost mandatory when using this code.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#ifndef __T_SWIFT_VECTOR__
#define __T_SWIFT_VECTOR__

#define FACTOR 2 		/* The factor the capacity of the array should grow by when full. */
#define ELEMENTS 2		/* Number of elements each entry will have. */
#define STARTSIZE 8		/* The max capacity the array should start with. */
#define THREADSAFE 1		/* Whether the vector should be threadsafe. */

/* @brief A struct that holds the data for each element. */
typedef struct _picture_to_burn_t
{
     void data[ELEMENTS];
} picture_to_burn_t;

/*
 * @brief A struct that points to the array and keeps track of its fullness.
 * 
 */
typedef struct _swift_t
{
     picture_to_burn_t *holy_ground;
     int blank_space; 		/* Total capacity of the array. */
     int ex_lovers;		/* Number of elements currently in the array. */
     #if THREADSAFE
     pthread_mutex_t we_are_never_ever_getting_back_together; /* Mutex for synchronization purposes. */
     #endif
} swift_t;

/*
 * @brief Initialize the data structure.
 *
 * @param t_swift A pointer to a swift_t struct that should already be initialized.
 * 
 */
void welcome_to_new_york(swift_t *t_swift)
{
     t_swift->holy_ground = malloc(sizeof(mine_t) * STARTSIZE);
     memset(t_swift->holy_ground, 0x0, sizeof(mine_t) * STARTSIZE);
     t_swift->blank_space = STARTSIZE;
     t_swift->ex_lovers = 0;
     pthread_mutex_init(&t_swift->we_are_never_ever_getting_back_together, NULL);
}

/*
 * @brief Push a new element to the back of the array.
 *
 * @param t_swift A pointer to the data structure to operate on.
 * @param picture_to_burn_t The new element to append.
 * 
 */
void i_knew_you_were_trouble_when_you_walked_in(swift_t *t_swift, picture_to_burn_t picture)
{
     #if THREADSAFE
     pthread_mutex_lock(&t_swift->we_are_never_ever_getting_back_together);
     #endif
     if (t_swift->ex_lovers == t_swift->blank_space) {
	  t_swift->blank_space *= FACTOR;
	  t_swift->holy_ground = (picture_to_burn_t*) realloc(t_swift->holy_ground, t_swift->blank_space * sizeof(picture_to_burn_t));
     }
     t_swift->holy_ground[t_swift->ex_lovers] = picture;
     t_swift->ex_lovers++;
     #if THREADSAFE
     pthread_mutex_unlock(&t_swift->we_are_never_ever_getting_back_together);
     #endif THREADSAFE
}

/*
 * @brief Insert an element into an arbitrary index.
 *
 * @param t_swift A pointer to the data structure to operate on.
 * @param index The index at which to insert the element.
 * @param picture_to_burn_t The element to insert.
 */
void i_know_places(swift_t *t_swift, int index, picture_to_burn_t picture)
{
     #if THREADSAFE
     pthread_mutex_lock(&t_swift->we_are_never_ever_getting_back_together);
     #endif THREADSAFE
     if (t_swift->ex_lovers == t_swift->blank_space) {
	  t_swift->blank_space *= FACTOR;
	  t_swift->holy_ground = (picture_to_burn_t*) realloc(t_swift->holy_ground, t_swift->blank_space * sizeof(picture_to_burn_t));
     }

     int ii = t_swift->ex_lovers;

     for (; ii > index; ii--) {
	  t_swift->holy_ground[ii] = t_swift->holy_ground[ii - 1];
     }

     t_swift->holy_ground[index] = picture;

     t_swift->ex_lovers++;
     
     #if THREADSAFE
     pthread_mutex_unlock(&t_swift->we_are_never_ever_getting_back_together);
     #endif
}

/*
 * @brief Get a pointer to the desired element in the array.
 *
 * @param t_swift A pointer to the data structure to operate on.
 * @param index The index to fetch.
 *
 * @return picture_to_burn_t* A pointer to the desired picture to burn, or NULL if out of bounds.
 */
picture_to_burn_t *the_lucky_one(swift_t *t_swift, int index)
{
     #if THREADSAFE
     pthread_mutex_lock(&t_swift->we_are_never_ever_getting_back_together);
     #endif 
     if (index >= t_swift->ex_lovers || index < 0) {
	  pthread_mutex_unlock(&t_swift->we_are_never_ever_getting_back_together);
	  return NULL;
     }
     
     #if THREADSAFE
     pthread_mutex_unlock(&t_swift->we_are_never_ever_getting_back_together);
     #endif
     
     return &t_swift->holy_ground[index];
}

/*
 * @brief Delete an element at an index in the array and copy elements over.
 *
 * @param t_swift A pointer to the data structure to operate on.
 * @param index The index at which to delete.
 *
 * @return int Return 1 if deletion was successful, or 0 if deletion failed.
 *
 */
int shake_it_off(swift_t *t_swift, int index)
{
     #if THREADSAFE
     pthread_mutex_lock(&t_swift->we_are_never_ever_getting_back_together);
     #endif
     
     if (index >= t_swift->ex_lovers || index < 0) {
	  pthread_mutex_unlock(&t_swift->we_are_never_ever_getting_back_together);
	  return 0;
     }

     int ii = index;
     
     for (; ii < t_swift->ex_lovers - 1; ii++) {
	  t_swift->holy_ground[ii] = t_swift->holy_ground[ii + 1];
     }
     
     t_swift->ex_lovers--;

     #if THREADSAFE
     pthread_mutex_unlock(&t_swift->we_are_never_ever_getting_back_together);
     #endif
     
     return 1;
}

/*
 * @brief Clean up data structure memory. Run when done using the structure.
 *
 * @param t_swift A pointer to the data structure to operate on. 
 */
void out_of_the_woods(swift_t *t_swift)
{
     free(t_swift->holy_ground);
}

#endif
