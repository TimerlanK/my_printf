#include<stdio.h>
#include<stdarg.h>
#include<string.h>


int my_string_length (char* string)                     // to measure length of string
{
	int length = 0;

	while (*string != '\0')
	{
		length++;
		string++;
	}

	return length+1;
}


int my_int_length(int argument)                         // to measure length of integer
{
	if (argument==0)
	{
		return 0;
	}

	return 1 + my_int_length(argument/10);
}

char* my_p_string(unsigned long argument, int base, int* length, char* buffer_pointer)      // converting from integer to string
{
    char BASE_SYMBOLS[] = "0123456789abcdef";                                       // BASE for converting from int to deca octa hexa

    if (argument == 0)                                                              // argument is zero
    {
        *buffer_pointer = BASE_SYMBOLS[0];
        (*length)++;
        return buffer_pointer;
    }
    while (argument != 0)
    {
        *buffer_pointer = BASE_SYMBOLS[argument % base];                            // converting number
        argument = argument / base;                                                 // going from right side of number to left

        if (argument != 0)                                                          //moving pointer from right to left
            {
                buffer_pointer--;
            }

        (*length)++;                                                                // measuring the length
    }

    return buffer_pointer;
}

char* my_int_string(int argument, int base, int* length, char* buffer_pointer)      // converting from integer to string
{
    char BASE_SYMBOLS[] = "0123456789abcdef";                                       // BASE for converting from int to deca octa hexa

    if (argument == 0)                                                              // argument is zero
    {
        *buffer_pointer = BASE_SYMBOLS[0];
        (*length)++;
        return buffer_pointer;
    }
    while (argument != 0)
    {
        *buffer_pointer = BASE_SYMBOLS[argument % base];                            // converting number
        argument = argument / base;                                                 // going from right side of number to left

        if (argument != 0)                                                          //moving pointer from right to left
            {
                buffer_pointer--;
            }

        (*length)++;                                                                // measuring the length
    }

    return buffer_pointer;
}



int my_printf(char * restrict format, ...)
{
    int break_second_loop=0;
    va_list arg;                                //arguments list
    va_start(arg, format);
    int length_to_print=0;
    int length_to_return = 0;

    while(*format != '\0')                      // going though string
    {
        while( *format != '%') 					// until % sign
        {
            if (*format == '\0')				// end of the string after %
            {
              break_second_loop = 1;			// break out of 2 loops
              break;
            }

            write(1, format, 1);				// printing every character
            format++;                           // moving pointer
            length_to_return++;
        }

        if (break_second_loop==1)				// break out of 2 loops
        {
          break;
        }

        format++;



        switch(*format)
        {


        	case 'c' :
            {
                int argument = va_arg(arg,int);        //Character argument
                int* buffer;							//pointer to argument
                buffer = &argument;

                write(1, buffer, 1);					//printing argument
                length_to_return++;
                break;
            }

        	case 's' :
			{
				char* argument = va_arg(arg,char *);              //Character argument
				if (argument==NULL)                                 // if string is a NULL case
                {
                    argument = "(null)";
                    length_to_print=my_string_length(argument);
                    write(1,argument,length_to_print-1);
                    length_to_print--;                              // for correct sum of total length???
                    length_to_return=length_to_return+length_to_print;
                    break;

                }
				else
                {
                    length_to_print=my_string_length(argument);
                    write(1,argument,length_to_print-1);
                    length_to_print--;                              // for correct sum of total length???
                    length_to_return=length_to_return+length_to_print;
                    break;
                }
			}

        	case 'd' :
            {


            	int argument = va_arg(arg,int);             //Character argument
                int base = 10;
                length_to_print = 0;


                char* buffer_pointer;                       //buffer_pointer is needed for write function
                char buffer_array[21];						//buffer size for int

                buffer_array[20] = '\0';
                buffer_pointer = &buffer_array[19];


                if (argument<0)                             //negative sign
                {
                    argument = -argument;
                    char negative_sign = '-';
                    write(1,&negative_sign, 1);
                    length_to_return++;
                }



                buffer_pointer = my_int_string(argument, base,&length_to_print, buffer_pointer);
                write(1, buffer_pointer, length_to_print);					                            //printing argument
                length_to_return=length_to_return+length_to_print;
                break;

            }


            case 'u' :
            {


            	int argument = va_arg(arg,int);             //Character argument
                int base = 10;
                length_to_print = 0;


                char* buffer_pointer;                       //buffer_pointer is needed for write function
                char buffer_array[21];						//buffer size for int

                buffer_array[20] = '\0';
                buffer_pointer = &buffer_array[19];


                if (argument<0)                             //negative sign
                {
                    argument = -argument;
                }



                buffer_pointer = my_int_string(argument, base,&length_to_print, buffer_pointer);
                write(1, buffer_pointer, length_to_print);					                            //printing argument
                length_to_return=length_to_return+length_to_print;
                break;

            }


        	case 'o' :
			{
                unsigned int argument = va_arg(arg,unsigned int);
                int base = 8;
                length_to_print = 0;

                char* buffer_pointer;
                char buffer_array[21];						//buffer size for int

                buffer_array[20] = '\0';
                buffer_pointer = &buffer_array[19];

                buffer_pointer = my_int_string(argument, base,&length_to_print, buffer_pointer);
                write(1, buffer_pointer, length_to_print);					//printing argument
                length_to_return=length_to_return+length_to_print;
                break;

			}

			case 'x' :
			{
                unsigned int argument = va_arg(arg,unsigned int);
                int base = 16;
                length_to_print = 0;

                char* buffer_pointer;
                char buffer_array[21];						//buffer size for int

                buffer_array[20] = '\0';
                buffer_pointer = &buffer_array[19];

                buffer_pointer = my_int_string(argument, base,&length_to_print, buffer_pointer);
                write(1, buffer_pointer, length_to_print);					//printing argument
                length_to_return=length_to_return+length_to_print;
                break;

			}

            case 'p' :
			{
                unsigned long argument = (unsigned long)va_arg(arg,void *);
                int base = 16;
                length_to_print = 0;

                char* buffer_pointer;
                char buffer_array[21];						//buffer size for int

                buffer_array[20] = '\0';
                buffer_pointer = &buffer_array[19];

                buffer_pointer = my_p_string(argument, base,&length_to_print, buffer_pointer);

                char str[]="0x7ffc";
                char* buffer;							//pointer to str
                buffer = str;

                write(1, str, 2);					//printing argument

                write(1, buffer_pointer, length_to_print);					//printing argument
                length_to_return=length_to_return+length_to_print;
                length_to_return=length_to_return+2;
                break;

			}
        }

        format++;
    }


    va_end(arg);


    return length_to_return;
}



int main()
{
    int text1=my_printf("Hello world!\n");
    int text2=printf("Hello world!\n");


    printf("%i\n",text1);
    printf("%i\n",text2);


    text1=my_printf("%c!\n", 'H');
    text2=printf("%c!\n", 'H');


    printf("%i\n",text1);
    printf("%i\n",text2);


    text1=my_printf("%c%c%c%c%c!\n", 'H', 'e', 'l', 'l', 'o');
    text2=printf("%c%c%c%c%c!\n", 'H', 'e', 'l', 'l', 'o');


    printf("%i\n",text1);
    printf("%i\n",text2);


    text1=my_printf("Hello %s!\n", "QWASAR.IO");
    text2=printf("Hello %s!\n", "QWASAR.IO");


    printf("%i\n",text1);
    printf("%i\n",text2);


    text1=my_printf("Hello %s %s!\n", "Mr", "Gaetan");
    text2=printf("Hello %s %s!\n", "Mr", "Gaetan");


    printf("%i\n",text1);
    printf("%i\n",text2);


    text1=my_printf("NULL STRING %s!\n", (char*)NULL);
    text2=printf("NULL STRING %s!\n", (char*)NULL);


    printf("%i\n",text1);
    printf("%i\n",text2);


    text1=my_printf("%d!\n", 1337);
    text2=printf("%d!\n", 1337);


    printf("%i\n",text1);
    printf("%i\n",text2);



    text1=my_printf("%d - %d - %d!\n", 2048, 0, -1337);
    text2=printf("%d - %d - %d!\n", 2048, 0, -1337);


    printf("%i\n",text1);
    printf("%i\n",text2);


    text1=my_printf("%o!\n", 100);
    text2=printf("%o!\n", 100);


    printf("%i\n",text1);
    printf("%i\n",text2);



    text1=my_printf("%u!\n", 1337);
    text2=printf("%u!\n", 1337);


    printf("%i\n",text1);
    printf("%i\n",text2);


    text1=my_printf("%x!\n", 14);
    text2=printf("%x!\n", 14);


    printf("%i\n",text1);
    printf("%i\n",text2);


    int variable=1;
    int *any_variable = &variable;


    text1=my_printf("%p!\n", any_variable);
    text2=printf("%p!\n", any_variable);


    printf("%i\n",text1);
    printf("%i\n",text2);





    return 0;
}
