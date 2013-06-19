#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>

#include "unicode/unistr.h"
#include "unicode/utypes.h"
#include "unicode/locid.h"
#include "unicode/coll.h"
#include "unicode/tblcoll.h"
#include "unicode/coleitr.h"
#include "unicode/sortkey.h"

/**
 * Compre function enables ascending order sorting.
 * @return true is source needs to come before target
 *         false if target need to come before source
 */
bool compare_using_collator (UnicodeString const& source, UnicodeString const& target) {
    UErrorCode status = U_ZERO_ERROR;
    Collator      *myCollator = 0;
    Collator::EComparisonResult result    = Collator::EQUAL;
    myCollator = Collator::createInstance(Locale("ru", "RU"), status);
    if (U_FAILURE(status)){
        std::cout << "Failed to create ru locale";
        return false;
    }
    result = myCollator->compare(source, target);
    if (result == UCOL_GREATER) {
        return false;
    }
    return true;
}

UBool collateWithLocaleInCPP(const Locale& locale, UErrorCode& status)
{
    UnicodeString dispName; 
    UnicodeString source("n");
    UnicodeString target("d");
    Collator::EComparisonResult result    = Collator::EQUAL;
    Collator      *myCollator = 0;
    CollationKey sourceKey;
    CollationKey targetKey; 
    if (U_FAILURE(status))  {
        return FALSE;
    }
    myCollator = Collator::createInstance(locale, status);
    if (U_FAILURE(status)){
        locale.getDisplayName(dispName);
        /*Report the error with display name... */
        fprintf(stderr,
                "%s: Failed to create the collator for : \"%s\"\n", dispName);
        return FALSE;
    }
    result = myCollator->compare(source, target);
    /* result is 1, secondary differences only for ignorable space characters*/
    if (result != UCOL_GREATER) {
        fprintf(stderr,
                "Comparing two strings with only secondary differences in C failed.\n");
        return FALSE;
    }

    std::cout << "Sorting array { n, , d, nn}" << std::endl;
    UnicodeString list [] = { "n", "", "d", "nn"};
    std::sort(list, list + 4, compare_using_collator);
    for (int i = 0; i < 4; i++) {
        std::string normal;
        list[i].toUTF8String(normal);
        std::cout << normal << std::endl;
    }
    return TRUE;
}
int main()  {
    UErrorCode status = U_ZERO_ERROR;
    fprintf(stdout, "\n");
    if (collateWithLocaleInCPP(Locale("ru", "RU"), status) != TRUE)  {
        fprintf(stderr,
                "Collate with locale in C++ failed.\n");
    } else  {
        fprintf(stdout, "Collate with Locale C++ example worked!!\n");
    }
    return 0;
} 
