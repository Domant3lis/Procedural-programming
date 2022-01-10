# Preface
This document describes the coding style used in this codebase.
`...` (three dots) in this document mean omitted code, because it is not relevant in that section.

Author: Domantas Keturakis
Email: domantas.keturakis@mif.stud.vu.lt

Version: 1.0

# Table Of Contents
// TODO

# Naming conventions
## Variables
All variables are named in snake_case, such as this: `int a_really_long_variable_name`. Constants are named all caps with _ as a separator between words, e.g.: `const char *STR_HELLO_WORLD = "Hello, World!"` 

## Functions
Functions follow a verb + noun convention e.g.: `get_thing()`, except if they are associated with certain custom types (see below).

## Structs and Enums
Structs and enums are named with words starting with capital letters no underscores, such as this: `BigNode`. Functions associated with these structs and enums begin with struct name and then follow snake_case convention, e.g.: `BigNode_delete_at(...)`


# Indentation and spacing
Each scope gets indented with tabs. Curly brackets get a line of their own (except in a do while loop, the closing bracket should be in the same line there `while` keyword is).
```
int main()
{
    ...
    for (...)
    {
        ...
        if (...)
        {
            ...
        }
    }
}
```

## If, else, if else statements
If, else, if else statements must have a space between keyword and parentheses.
```
if (...)
{
    ...
}
```

Conditions involving several variables or constants must be parenthesized. 
```
if (cond_a || (a > b) || (c == a + 2))
```

If a condition has only one modifiable value and the operators `!=` or `==` are involved then the value which cannot change must be placed on the right.
```
if ((SOME_CONST == var_a) || (0 == var_b))
``` 

Conditions there where are different boolean operators must be surrounded by additional parentheses.
```
if (cond_a || ((a > b) && (c == a + 2)))
```

### Multiline conditions
If the condition is too long to fit into one line, then they can be split into several lines, where outer parentheses and each condition get their own line followed by boolean operators.
```
if
(
    some_var != some_other_var ||
    (
        (SOME_TYPE_OF_CONSTANT != some_struct.value)  &&
        (SOME_TYPE_OF_OTHER_CONSTANT != some_struct.value) 
    ) ||
    other_var == SOME_CONST
)
{
    ...
}

```

## Exceptions
Some scopes (including curly brackets) which are short (soft limit of about 50 characters) can be written in one line, e.g.:
```
if (...)
    { ++iter; ++count; }
```

This would be cutting too close and not acceptable: 
```
bool cmp_ascii_case_insensitive(char left, char right)
    { return (left == right) || ((left + 20) == right) || (left == (right + 20)); }
```


# Comments
Comments are always placed above the codeblock which they describe. Long comments are not broken up by manually entering newlines and instead rely on the developers editor line wrapping capabilities. If one wishes to separate comments by short paragraphs they must contain an empty commented line, such as this.:
```
// A really long but needed explanation
//
// Some other explanation
```

## Tags
Critical details, such as who is responsible for freeing allocated memory, are marked with `IMPORTANT:`. Features which are unfinished or are planned to be added in the future must be marked with `TODO:`. Different tags must be separated by an empty commented line.

## Example
```
// This function returns a string starting with a specified character `ch` from an array of strings (char **).
//
// IMPORTANT: this function copies the string and allocates memory only enough to store that string, thus the caller is responsible must free the returned string.
//
// TODO: Return NULL if none is found. As it is now, it returns the last string. 
char *get_string_starting_with(char **string_list, char ch)
{
    ...

    // Iterates through all strings
    for (...)
    {
       ... 
    }
}
```

# 
