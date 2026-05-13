#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "validation.h"
#include "contact.h"
#include "file.h"
/* ---------------- NAME VALIDATION ---------------- */
int validate_name(char *name)
{
    if(name[0] == '\0') 
        return 0; // Check if name is empty
    
    // Check each character for validity
    for(int i = 0; name[i] != '\0'; i++)
    {
        if(!isalpha(name[i]) && name[i] != ' ')
            return 0; // Return 0 if invalid character found
    }
    return 1; // Return 1 if all characters are valid
}
// Validate phone number - 10 digits starting with 6-9
int validate_phone(char *phone)
{
    if(strlen(phone) != 10)
        return 0; // Check if phone has exactly 10 digits
    
    if(phone[0] < '6' || phone[0] > '9')
        return 0; // Check if first digit is 6, 7, 8, or 9
    
    // Check if all characters are digits
    for(int i = 0; phone[i] != '\0'; i++)
    {
        if(!isdigit(phone[i]))
            return 0; // Return 0 if non-digit found
    }
    return 1; // Return 1 if phone is valid
}
// Validate email format with comprehensive checks
int validate_email(char *email)
{
    int at_count = 0;
    int at_index = -1;
    int dot_index = -1;

    int len = strlen(email);

    if(len < 6)
        return 0; // Check minimum email length

    // Check for valid characters and track @ and . positions
    for(int i = 0; email[i] != '\0'; i++)
    {
        if (!isalnum(email[i]) && email[i] != '@' &&
            email[i] != '.' && email[i] != '_')
            return 0; // Check for invalid characters

        if(email[i] == '@')
        {
            at_count++;
            at_index = i; // Store @ position
        }

        if(email[i] == '.')
        {
            if(i > 0 && email[i-1] == '.')
                return 0; // Prevent consecutive dots

            dot_index = i; // Store dot position
        }
    }
    
    // Validate @ symbol
    if(at_count != 1)
        return 0; // Must have exactly one @
    if(at_index <= 0 || at_index == len - 1)
        return 0; // @ cannot be at start or end
    if(!isalnum(email[at_index + 1]))
        return 0; // Character after @ must be alphanumeric
    
    // Validate dot
    if(dot_index == -1)
        return 0; // Must have at least one dot
    if(dot_index <= at_index + 1)
        return 0; // Dot must come after @
    if(dot_index >= len - 1)
        return 0; // Dot cannot be at end

    // Check for .com domain
    if(len < 4 || strcmp(&email[len - 4], ".com") != 0)
        return 0; // Must end with .com

    // Check for invalid characters before @
    if(email[at_index - 1] == '.' || email[at_index - 1] == '_')
        return 0; // Cannot have . or _ immediately before @

    return 1; // Return 1 if email is valid
}
// End of validation functions

