#include <stdio.h>
#include "unicode/unistr.h"
#include "unicode/utypes.h"
#include "unicode/locid.h"
#include "unicode/coll.h"
#include "unicode/tblcoll.h"
#include "unicode/coleitr.h"
#include "unicode/sortkey.h"
UBool collateWithLocaleInCPP(const Locale& locale, UErrorCode& status)
{
    UnicodeString dispName; 
    UnicodeString source("n");
    UnicodeString target("d");
    Collator::EComparisonResult result    = Collator::EQUAL;
    CollationKey sourceKey;
    CollationKey targetKey; 
    Collator      *myCollator = 0;
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
