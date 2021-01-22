/* *********************************** */
/*                                     */
/*      LibHash project                */
/*                                     */
/*      Created by Artur Makhnach      */
/*      github.com/DippyArtu           */
/*      artum.me                       */
/*                                     */
/* *********************************** */

#ifndef LEM_IN_PRIME_H
# define LEM_IN_PRIME_H

# include <math.h>

// A prime used for the hashing algorithm
// - Should be larger than the size of the ASCII alphabet (128)
# define HT_PRIME_1 179
# define HT_PRIME_2 1231

int 						is_prime(const int x);																		// Check if x is prime
int 						next_prime(int x);																			// Return x or prime next after x

#endif
