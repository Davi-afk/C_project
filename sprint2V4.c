#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

char *mystristr(char *haystack, char *needle)
{
   if ( !*needle )
   {
      return haystack;
   }
   for ( ; *haystack; ++haystack )
   {
      if ( toupper(*haystack) == toupper(*needle) )
      {
         /*
          * Matched starting char -- loop through remaining chars.
          */
         const char *h, *n;
         for ( h = haystack, n = needle; *h && *n; ++h, ++n )
         {
            if ( toupper(*h) != toupper(*n) )
            {
               break;
            }
         }
         if ( !*n ) /* matched all of 'needle' to null termination */
         {
            return haystack; /* return the start of the match */
         }
      }
   }
   return 0;
}

struct node {
    char *tag;
    struct node * prev;
    struct node * next;
}*head, *last;

struct tag {
    bool print;
    struct tag *prev;
    struct tag *next;
}*head1, *last1;

struct list {
    char *words;
    struct list *prev;
    struct list *next;
}*first1, *end;

struct list *newlist;
bool e = true;
char* replaceWord(const char* s, const char* oldW,
                  const char* newW)
{
    char* result;
    int i, cnt = 0;
    int newWlen = strlen(newW);
    int oldWlen = strlen(oldW);
  
    // Counting the number of times old word
    // occur in the string
    for (i = 0; s[i] != '\0'; i++) {
        if (strstr(&s[i], oldW) == &s[i]) {
            cnt++;
  
            // Jumping to index after the old word.
            i += oldWlen - 1;
        }
    }
  
    // Making new string of enough length
    result = (char*)malloc(i + cnt * (newWlen - oldWlen) + 1);
  
    i = 0;
    while (*s) {
        // compare the substring with the result
        if (strstr(s, oldW) == s) {
            strcpy(&result[i], newW);
            i += newWlen;
            s += oldWlen;
        }
        else
            result[i++] = *s++;
    }
    result[i] = '\0';
    if (e)
   {
        first1 = (struct list *)malloc(sizeof(struct list));
                        if(first1 != NULL)
                        {
                         first1->words = result;
                        first1->prev = NULL;
                        first1->next = NULL;
                        end = first1;
                 }
                 e = false;
   }
   else
                 {
                 newlist = (struct list *)malloc(sizeof(struct list));
                if(newlist != NULL)
                {
                    newlist->words = result;
                    newlist->prev = end; 
                    newlist->next = NULL;
                    if (end != NULL)
                    {
                    end->next = newlist; 
                    }
                    end = newlist;      
                }
                 }
    return result;
}

char* substring(char*, int, int);
char *substring(char *string, int position, int length)
{
   int c;
 
   char *p = malloc(length+2);
   for (c = 0; c < length; c++)
   {
      *(p+c) = *(string+position-1);      
      string++;  
   }
 
   *(p+c) = '\0';
   if (e)
   {
        first1 = (struct list *)malloc(sizeof(struct list));
                        if(first1 != NULL)
                        {
                         first1->words = p;
                        first1->prev = NULL;
                        first1->next = NULL;
                        end = first1;
                 }
                 e = false;
   }
   else
                 {
                 newlist = (struct list *)malloc(sizeof(struct list));
                if(newlist != NULL)
                {
                    newlist->words = p;
                    newlist->prev = end; 
                    newlist->next = NULL;
                    if (end != NULL)
                    {
                    end->next = newlist; 
                    }
                    end = newlist;      
                }
                 }
   return p;
}
void displayListFromFirst()
{
    struct node * temp;

    if(head == NULL)
    {
        printf("List is empty.");
    }
    else
    {
        temp = head;

        while(temp != NULL)
        {
            printf("%s", temp->tag);

            
            /* Move the current pointer to next node */
            temp = temp->next;
        }
    }
}
//make sure levels are correct
//unrecognized non match end tag
int main(int argc, const char *argv[]) {
    bool yy = false;
    int word_count = 0;
    int specific_word_count = 0;
    struct node *newNode;
    struct tag *newTag;
    int W = 0;
    FILE *in;
    FILE *out;
    bool Word_Count = false;
    const char *find_frequency;
    const char *filein_name;
    const char *fileout_name;
    int level = 0;
    bool unclosed_level3 = false;
    bool unclosed_level4 = false;
    bool unclosed_title = false;
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-c") == 0)
        {
            Word_Count = true;
        }
        else if (strcmp(argv[i], "-f") == 0)
        {
            find_frequency = argv[i + 1];
            yy = true;
        }
        else if (strstr(argv[i], ".") != NULL)
        {
            filein_name = argv[i];
            fileout_name = argv[i + 1];
            break;
        }
    }
    struct tag *current;
    char table[26][1024] = {
                   "&nbsp;",
                   "&#160;",
                   "&lt;",
                   "&#60;",
                   "&gt;",
                   "&#62;",
                   "&amp;",
                   "&#38;",
                   "&quot;",
                   "&#34;",
                   "&apos;",
                   "&#39;",
                   "&cent;",
                   "&#162;",
                   "&pound;",
                   "&#163;",
                   "&yen;",
                   "&#165;",
                   "&euro;",
                   "&#8364;",
                   "&copy;",
                   "&#169;",
                   "&reg;",
                   "&#174;",
                   "&sect;",
                   "&#167;"
                 };
                 char replace_table[26][1024] = {
                   " ",
                   " ",
                   "<",
                   "<",
                   ">",
                   ">",
                   "&",
                   "&",
                   "\"",
                   "\"",
                   "'",
                   "'",
                   "cent",
                   "cent",
                   "pound",
                   "pound",
                   "yen",
                   "yen",
                   "euro",
                   "euro",
                   "copyright",
                   "copyright",
                   "trademark",
                   "trademark",
                   "section",
                   "section"
                 };
    current = (struct tag *)malloc(sizeof(struct tag)); 
    if ((in = fopen(filein_name, "r")) == NULL)
    {
        fprintf(stderr,"failed to open file");
        return(1);
    }
    out = fopen(fileout_name, "w");
    char line[1024];
    int size = 0;
    int line_size = 0;
    while (fscanf(in, "%s", line) == 1) 
    {
        size++;   
    }
    fseek(in, 0, SEEK_SET);
    int x = 0;
    while (fgets(line, 1000, in) != NULL)
    {
        line_size++;
    }
    fseek(in, 0, SEEK_SET);
    char file_lines[line_size][1024];
    char dup[line_size][1024];
    while (fgets(line, 1000, in) != NULL)
    {
        int u = 0;
        strcpy(file_lines[x], line);
        strcpy(dup[x], line);
        for (int i = 0; i < 26; i++)
        {
            if (strstr(dup[x], table[i]) != NULL)
            {
                strcpy(dup[x], replaceWord(dup[x], table[i], replace_table[i]));
            }
        }
        while ((strstr(dup[x], "&") != NULL) && (strstr(dup[x], ";") != NULL))
        {
            char T[1000];
            strcpy(T, dup[x]);
            char *words = strtok(dup[x], " ");
            bool a = false;
            while (words != NULL)
            {
                if ((strstr(words, "&") != NULL) && (strstr(words, ";") != NULL))
                {
                    a = true;
                    break;
                }
                words = strtok(NULL, " ");
            }
            if (a)
                {
                    int OO = 0;
                    int O = 0;
                    for (int i = 0; i < strlen(words); i++)
                    {
                        if (words[i] == '&')
                        {
                            O = i;
                        }
                        else if (words[i] == ';')
                        {
                            OO = i;
                            break;
                        }
                    }
                    strcpy(dup[x], replaceWord(T, substring(words, O + 1, OO - O + 1 ), ""));
                }
        }
        
        while (true)
        {
            u++;
            if (u > 35)
            {
                break;
            }
            int len = 0;
            for (int i = 0; i <strlen(dup[x]); i++)
            {
                if ((dup[x][i] == ' ') || (dup[x][i] == '\n') || (dup[x][i] == '\t'))
                {
                    len++;
                }
            }
            if (len == strlen(dup[x]))
        {
                 if (W == 0)
                 {
                        head = (struct node *)malloc(sizeof(struct node));
                        if(head != NULL)
                        {
                         head->tag = "\n";
                        head->prev = NULL;
                        head->next = NULL;
                        last = head;
                 }
                 W++;
                 }
                 else
                 {
                 newNode = (struct node *)malloc(sizeof(struct node));
                if(newNode != NULL)
                {
                    newNode->tag = "\n";
                    newNode->prev = last; 
                    newNode->next = NULL;
                    if (last != NULL)
                    {
                    last->next = newNode; 
                    }
                    last = newNode;      
                }
                 }
            break;
        }
            if (strstr(dup[x], "<") != NULL)
        {
            if (strstr(dup[x], ">") == NULL)
            {
                char *temp = malloc(10000);
                 if (e)
   {
        first1 = (struct list *)malloc(sizeof(struct list));
                        if(first1 != NULL)
                        {
                         first1->words = temp;
                        first1->prev = NULL;
                        first1->next = NULL;
                        end = first1;
                 }
                 e = false;
   }
   else
                 {
                 newlist = (struct list *)malloc(sizeof(struct list));
                if(newlist != NULL)
                {
                    newlist->words = temp;
                    newlist->prev = end; 
                    newlist->next = NULL;
                    if (end != NULL)
                    {
                    end->next = newlist; 
                    }
                    end = newlist;      
                }
                 }
                strcpy(temp, dup[x]);
                while (strstr(temp, ">") == NULL)
                {
                    fgets(line, 1000, in);
                    temp = strcat(temp, line);
                }
                int z = 0;
                int zz = 0;
                 for (int k = 0; k < strlen(temp); k++)
                 {
                     if (temp[k] == '<')
                         {
                             zz = k;
                         }
                     if (temp[k] == '>')
                     {
                         z = k;
                         break;
                     }
                 }
                 if (W == 0)
                 {
                        head = (struct node *)malloc(sizeof(struct node));
                        if(head != NULL)
                        {
                         head->tag = substring(temp, zz+1, (z - zz + 1));
                        head->prev = NULL;
                        head->next = NULL;
                        last = head;
                 }
                 W++;
                 strcpy(dup[x], substring(temp, z+2, strlen(temp)));
                 }
                 else
                 {
                     if (zz == 0)
                     {
                         newNode = (struct node *)malloc(sizeof(struct node));

                if(newNode != NULL)
                {
                    newNode->tag = substring(temp, zz+1, (z - zz + 1));
                    newNode->prev = last; 
                    newNode->next = NULL;
                    last->next = newNode; 
                    last = newNode;       
                }
                strcpy(dup[x], substring(temp, z+2, strlen(temp)));
                 }
                 else
                 {
                 newNode = (struct node *)malloc(sizeof(struct node));

                if(newNode != NULL)
                {
                    newNode->tag = substring(temp, 1, zz);
                    newNode->prev = last; 
                    newNode->next = NULL;
                    last->next = newNode; 
                    last = newNode;       
                }
                strcpy(dup[x], substring(temp, zz+1, strlen(temp)));
                 }
                     }
            }
            else
            {
            int z = 0;
            int zz = 0;
                 for (int k = 0; k < strlen(dup[x]); k++)
                 {
                     if (dup[x][k] == '<')
                         {
                             zz = k;
                         }
                     if (dup[x][k] == '>')
                     {
                         z = k;
                         break;
                     }
                 }
                 if (W == 0)
                 {
                        head = (struct node *)malloc(sizeof(struct node));
                        if(head != NULL)
                        {
                         head->tag = substring(dup[x], zz+1, (z - zz + 1));
                        head->prev = NULL;
                        head->next = NULL;
                        last = head;
                 }
                 W++;
                 strcpy(dup[x], substring(dup[x], z+2, strlen(dup[x])));
                 }
                 else
                 {
                     if (zz == 0)
                     {
                         newNode = (struct node *)malloc(sizeof(struct node));

                if(newNode != NULL)
                {
                    newNode->tag = substring(dup[x], zz+1, (z - zz + 1));
                    newNode->prev = last; 
                    newNode->next = NULL;
                    last->next = newNode; 
                    last = newNode;       
                }
                strcpy(dup[x], substring(dup[x], z+2, strlen(dup[x])));
                 }
                 else
                 {
                 newNode = (struct node *)malloc(sizeof(struct node));

                if(newNode != NULL)
                {
                    newNode->tag = substring(dup[x], 1, zz);
                    newNode->prev = last; 
                    newNode->next = NULL;
                    last->next = newNode; 
                    last = newNode;       
                }
                strcpy(dup[x], substring(dup[x], zz+1, strlen(dup[x])));
                 }
                     }
            }
                     
        }
        else
        {
            newNode = (struct node *)malloc(sizeof(struct node));

                if(newNode != NULL)
                {
                    newNode->tag = substring(dup[x], 1, strlen(dup[x]));
                    newNode->prev = last; 
                    newNode->next = NULL;
                    if (last != NULL)
                    {
                    last->next = newNode;
                    }
                    last = newNode;       
                }
                break;
        }
        }
        x++;
    }
    int unknown = 0;
    bool print_current = false;
    bool first = true;
    struct node *temp2 = head;
    bool body_tag = false;
    bool html_tag = false;
    char *attribute = NULL;
    while (temp2 != NULL)
    {
        if (level >= 5)
        {
        fclose(out);
            out = NULL;
                    out = fopen(fileout_name, "w");
                    fclose(out);
                        out = NULL;
                    yy = false;
                    Word_Count = false;
                    break;
        }
        if (strcasecmp(temp2->tag, "<html>") == 0)
        {
            if (first)
            {
                current->print = true;
                current->next = NULL;
                current->prev = NULL;
                head1 = current;
                last1 = current;
                first = false;
                level++;
                if (attribute != NULL)
            {
                fprintf(out, "%s ", attribute);
                attribute = NULL;
            }
            }
            else
            {
                    fclose(out);
                        out = NULL;
                    out = fopen(fileout_name, "w");
                    fclose(out);
                        out = NULL;
                    yy = false;
                    Word_Count = false;
                    break;
            }
            temp2 = temp2->next;
        }
        else if (strcasecmp(temp2->tag, "<title>") == 0)
        {
            if (level == 1)
            {
            bool found = false;
                int current_recognized_tags = 0;
                struct node *temp6 = temp2->next;
                char *current_tag = temp2->tag;
                char *current_end_tag = malloc(strlen(temp2->tag) * 100);
                free(current_end_tag);
                current_end_tag = strcat(substring(current_tag, 1, 1), "/");
                current_end_tag = strcat(current_end_tag, substring(current_tag, 2,strlen(current_tag)));
                while (temp6 != NULL)
                {
                    char *temp7 = temp6->tag;
                    if ((strstr(temp7, "<") != NULL) && (strstr(temp7, ">") != NULL) && (strstr(temp7, " ") != NULL))
                    {
                        temp7 = substring(temp7, 1, strlen(temp7) - strlen((strstr(temp7, " "))));
                        temp7 = strcat(temp7, ">");
                    }
                    if ((strcasecmp(temp7, "<p>") == 0) || (strcasecmp(temp7, "<h1>") == 0) || (strcasecmp(temp7, "<h2>") == 0) || (strcasecmp(temp7, "<h3>") == 0) || (strcasecmp(temp7, "<h4>") == 0) || (strcasecmp(temp7, "<h5>") == 0) || (strcasecmp(temp7, "<h6>") == 0) || (strcasecmp(temp7, "<ul>") == 0) || (strcasecmp(temp7, "<ol>") == 0) || (strcasecmp(temp7, "<section>") == 0))
                    {
                       current_recognized_tags = current_recognized_tags + 1;
                        temp6 = temp6->next;
                    }
                    else if ((strcasecmp(temp7, "<body>") == 0) || (strcasecmp(temp7, "<title>") == 0))
                    {
                        unclosed_title = true;
                        level++;
                        break;
                    }
                    else if ((strcasecmp(temp7, "<li>") == 0) || (strcasecmp(temp7, "<b>") == 0) || (strcasecmp(temp7, "<i>") == 0) || (strcasecmp(temp7, "<strong>") == 0) || (strcasecmp(temp7, "<em>") == 0) || (strcasecmp(temp7, "<small>") == 0) || (strcasecmp(temp7, "<code>") == 0) || (strcasecmp(temp7, "<pre>") == 0) || (strcasecmp(temp7, "<sub>") == 0) || (strcasecmp(temp7, "<sup>") == 0) || (strcasecmp(temp7, "<a>") == 0) || (strcasecmp(temp7, "<label>") == 0) || (strcasecmp(temp7, "<abbr>") == 0) || (strcasecmp(temp7, "<addr>") == 0) || (strcasecmp(temp7, "<q>") == 0) || (strcasecmp(temp7, "<blockquote>") == 0) || (strcasecmp(temp7, "<div>") == 0) || (strcasecmp(temp7, "<cite>") == 0))
                    {
                        current_recognized_tags = current_recognized_tags + 1;
                        temp6 = temp6->next;
                    }
                    else if ((strcasecmp(temp7, "</li>") == 0) || (strcasecmp(temp7, "</b>") == 0) || (strcasecmp(temp7, "</i>") == 0) || (strcasecmp(temp7, "</strong>") == 0) || (strcasecmp(temp7, "</em>") == 0) || (strcasecmp(temp7, "</small>") == 0) || (strcasecmp(temp7, "</code>") == 0) || (strcasecmp(temp7, "</pre>") == 0) || (strcasecmp(temp7, "</sub>") == 0) || (strcasecmp(temp7, "</sup>") == 0) || (strcasecmp(temp7, "</a>") == 0) || (strcasecmp(temp7, "</label>") == 0) || (strcasecmp(temp7, "</abbr>") == 0) || (strcasecmp(temp7, "</addr>") == 0) || (strcasecmp(temp7, "</q>") == 0) || (strcasecmp(temp7, "</blockquote>") == 0) || (strcasecmp(temp7, "</div>") == 0) || (strcasecmp(temp7, "</cite>") == 0))
                    {
                        current_recognized_tags = current_recognized_tags - 1;
                        temp6 = temp6->next;
                    }
                    else if ((strcasecmp(temp7, "</html>") == 0))
                    {
                        unclosed_title = true;
                        level++;
                        break;
                    }
                    else if ((strcasecmp(temp7, current_end_tag) == 0))
                    {
                        if (first)
            {
                current->print = false;
                current->next = NULL;
                current->prev = NULL;
                head1 = current;
                last1 = current;
                first = false;
            }
            else
            {
                newTag = (struct tag *)malloc(sizeof(struct tag));
                newTag->next = NULL;
                newTag->prev = current;
                newTag->print = true;
                current = newTag;
                    if (last1 != NULL)
                    {
                    last1->next = newTag; 
                    }
                    last1 = newTag;  
            }
            level++;
            if (attribute != NULL)
            {
                fprintf(out, "%s ", attribute);
                attribute = NULL;
            }
            temp2 = temp2->next;
            found = true;
            break;
                    }
                    else 
                    {
                        temp6 = temp6->next;
                    }
                }
                if (!found)
                {
                temp2 = temp2->next;
                unknown++;
                }
            }
            else
            {
                    fclose(out);
                        out = NULL;
                    out = fopen(fileout_name, "w");
                    fclose(out);
                        out = NULL;
                    yy = false;
                    Word_Count = false;
                    break;
            }
        }
        else if (strcasecmp(temp2->tag, "<body>") == 0)
        {
            if (unclosed_title)
            {
                unknown--;
                unclosed_title = false;
                level--;
            }
            if ((level == 1) && !body_tag)
            {
                newTag = (struct tag *)malloc(sizeof(struct tag));
                newTag->next = NULL;
                newTag->prev = current;
                newTag->print = true;
                current = newTag;
                    if (last1 != NULL)
                    {
                    last1->next = newTag; 
                    }
                    last1 = newTag;   
                    level++;
                    temp2 = temp2->next;
                    if (attribute != NULL)
            {
                fprintf(out, "%s ", attribute);
                attribute = NULL;
            }
            }
            else
            {
                    fclose(out);
                        out = NULL;
                    out = fopen(fileout_name, "w");
                    fclose(out);
                        out = NULL;
                    yy = false;
                    Word_Count = false;
                    break;
            }
        }
        else if ((strcasecmp(temp2->tag, "<p>") == 0) || (strcasecmp(temp2->tag, "<h1>") == 0) || (strcasecmp(temp2->tag, "<h2>") == 0) || (strcasecmp(temp2->tag, "<h3>") == 0) || (strcasecmp(temp2->tag, "<h4>") == 0) || (strcasecmp(temp2->tag, "<h5>") == 0) || (strcasecmp(temp2->tag, "<h6>") == 0) || (strcasecmp(temp2->tag, "<ul>") == 0) || (strcasecmp(temp2->tag, "<ol>") == 0) || (strcasecmp(temp2->tag, "<section>") == 0))
        {
            if (unclosed_level3)
            {
                unknown--;
                unclosed_level3 = false;
                level--;
            }
            if (unclosed_level4)
            {
                unknown--;
                unclosed_level4 = false;
                level--;
            }
            if (level == 2)
            {
                bool found = false;
                int current_recognized_tags = 0;
                struct node *temp6 = temp2->next;
                char *current_tag = temp2->tag;
                char *current_end_tag = malloc(strlen(temp2->tag) * 100);
                free(current_end_tag);
                current_end_tag = strcat(substring(current_tag, 1, 1), "/");
                current_end_tag = strcat(current_end_tag, substring(current_tag, 2,strlen(current_tag)));
                while (temp6 != NULL)
                {
                    char *temp7 = temp6->tag;
                    if ((strstr(temp7, "<") != NULL) && (strstr(temp7, ">") != NULL) && (strstr(temp7, " ") != NULL))
                    {
                        temp7 = substring(temp7, 1, strlen(temp7) - strlen((strstr(temp7, " "))));
                        temp7 = strcat(temp7, ">");
                    }
                    if (((strcasecmp(temp7, "</p>") == 0) || (strcasecmp(temp7, "</h1>") == 0) || (strcasecmp(temp7, "</h2>") == 0) || (strcasecmp(temp7, "</h3>") == 0) || (strcasecmp(temp7, "</h4>") == 0) || (strcasecmp(temp7, "</h5>") == 0) || (strcasecmp(temp7, "</h6>") == 0) || (strcasecmp(temp7, "</ul>") == 0) || (strcasecmp(temp7, "</ol>") == 0) || (strcasecmp(temp7, "</section>") == 0)) && (strcasecmp(temp7, current_end_tag) != 0))
                    {
                        unclosed_level3 = true;
                        level++;
                        break;
                    }
                    else if ((strcasecmp(temp7, "</html>") == 0) || (strcasecmp(temp7, "</body>") == 0))
                    {
                        unclosed_level3 = true;
                        level++;
                        break;
                    }
                    else if ((strcasecmp(temp7, "<li>") == 0) || (strcasecmp(temp7, "<b>") == 0) || (strcasecmp(temp7, "<i>") == 0) || (strcasecmp(temp7, "<strong>") == 0) || (strcasecmp(temp7, "<em>") == 0) || (strcasecmp(temp7, "<small>") == 0) || (strcasecmp(temp7, "<code>") == 0) || (strcasecmp(temp7, "<pre>") == 0) || (strcasecmp(temp7, "<sub>") == 0) || (strcasecmp(temp7, "<sup>") == 0) || (strcasecmp(temp7, "<a>") == 0) || (strcasecmp(temp7, "<label>") == 0) || (strcasecmp(temp7, "<abbr>") == 0) || (strcasecmp(temp7, "<addr>") == 0) || (strcasecmp(temp7, "<q>") == 0) || (strcasecmp(temp7, "<blockquote>") == 0) || (strcasecmp(temp7, "<div>") == 0) || (strcasecmp(temp7, "<cite>") == 0))
                    {
                        current_recognized_tags = current_recognized_tags + 1;
                        temp6 = temp6->next;
                    }
                    else if ((strcasecmp(temp7, "</li>") == 0) || (strcasecmp(temp7, "</b>") == 0) || (strcasecmp(temp7, "</i>") == 0) || (strcasecmp(temp7, "</strong>") == 0) || (strcasecmp(temp7, "</em>") == 0) || (strcasecmp(temp7, "</small>") == 0) || (strcasecmp(temp7, "</code>") == 0) || (strcasecmp(temp7, "</pre>") == 0) || (strcasecmp(temp7, "</sub>") == 0) || (strcasecmp(temp7, "</sup>") == 0) || (strcasecmp(temp7, "</a>") == 0) || (strcasecmp(temp7, "</label>") == 0) || (strcasecmp(temp7, "</abbr>") == 0) || (strcasecmp(temp7, "</addr>") == 0) || (strcasecmp(temp7, "</q>") == 0) || (strcasecmp(temp7, "</blockquote>") == 0) || (strcasecmp(temp7, "</div>") == 0) || (strcasecmp(temp7, "</cite>") == 0))
                    {
                        current_recognized_tags = current_recognized_tags - 1;
                        temp6 = temp6->next;
                    }
                    else if (strcasecmp(temp7, current_tag) == 0)
                    {
                        unclosed_level3 = true;
                        level++;
                        break;
                    }
                    else if ((strcasecmp(temp7, current_end_tag) == 0))
                    {
                        if (first)
            {
                current->print = false;
                current->next = NULL;
                current->prev = NULL;
                head1 = current;
                last1 = current;
                first = false;
            }
            else
            {
                newTag = (struct tag *)malloc(sizeof(struct tag));
                newTag->next = NULL;
                newTag->prev = current;
                newTag->print = true;
                current = newTag;
                    if (last1 != NULL)
                    {
                    last1->next = newTag; 
                    }
                    last1 = newTag;  
            }
            level++;
            if (attribute != NULL)
            {
                fprintf(out, "%s ", attribute);
                attribute = NULL;
            }
            temp2 = temp2->next;
            found = true;
            break;
                    }
                    else 
                    {
                        temp6 = temp6->next;
                    }
                }
                if (!found)
                {
                temp2 = temp2->next;
                unknown++;
                }
            }
            else
            {
                    fclose(out);
                        out = NULL;
                    out = fopen(fileout_name, "w");
                    fclose(out);
                        out = NULL;
                    yy = false;
                    Word_Count = false;
                    break;
            }
        }
        else if ((strcasecmp(temp2->tag, "<li>") == 0) || (strcasecmp(temp2->tag, "<b>") == 0) || (strcasecmp(temp2->tag, "<i>") == 0) || (strcasecmp(temp2->tag, "<strong>") == 0) || (strcasecmp(temp2->tag, "<em>") == 0) || (strcasecmp(temp2->tag, "<small>") == 0) || (strcasecmp(temp2->tag, "<code>") == 0) || (strcasecmp(temp2->tag, "<pre>") == 0) || (strcasecmp(temp2->tag, "<sub>") == 0) || (strcasecmp(temp2->tag, "<sup>") == 0) || (strcasecmp(temp2->tag, "<a>") == 0) || (strcasecmp(temp2->tag, "<label>") == 0) || (strcasecmp(temp2->tag, "<abbr>") == 0) || (strcasecmp(temp2->tag, "<addr>") == 0) || (strcasecmp(temp2->tag, "<q>") == 0) || (strcasecmp(temp2->tag, "<blockquote>") == 0) || (strcasecmp(temp2->tag, "<div>") == 0) || (strcasecmp(temp2->tag, "<cite>") == 0))
        {
            if (unclosed_level4)
            {
                unknown--;
                unclosed_level4 = false;
                level--;
            }
            if (level == 3)
            {
                bool found = false;
                struct node *temp6 = temp2->next;
                char *current_tag = temp2->tag;
                char *current_end_tag = malloc(strlen(temp2->tag) * 100);
                free(current_end_tag);
                current_end_tag = strcat(substring(current_tag, 1, 1), "/");
                current_end_tag = strcat(current_end_tag, substring(current_tag, 2,strlen(current_tag)));
                while (temp6 != NULL)
                {
                    char *temp7 = temp6->tag;
                    if ((strstr(temp7, "<") != NULL) && (strstr(temp7, ">") != NULL) && (strstr(temp7, " ") != NULL))
                    {
                        temp7 = substring(temp7, 1, strlen(temp7) - strlen((strstr(temp7, " "))));
                        temp7 = strcat(temp7, ">");
                    }
                    if ((strcasecmp(temp7, "<li>") == 0) || (strcasecmp(temp7, "<b>") == 0) || (strcasecmp(temp7, "<i>") == 0) || (strcasecmp(temp7, "<strong>") == 0) || (strcasecmp(temp7, "<em>") == 0) || (strcasecmp(temp7, "<small>") == 0) || (strcasecmp(temp7, "<code>") == 0) || (strcasecmp(temp7, "<pre>") == 0) || (strcasecmp(temp7, "<sub>") == 0) || (strcasecmp(temp7, "<sup>") == 0) || (strcasecmp(temp7, "<a>") == 0) || (strcasecmp(temp7, "<label>") == 0) || (strcasecmp(temp7, "<abbr>") == 0) || (strcasecmp(temp7, "<addr>") == 0) || (strcasecmp(temp7, "<q>") == 0) || (strcasecmp(temp7, "<blockquote>") == 0) || (strcasecmp(temp7, "<div>") == 0) || (strcasecmp(temp7, "<cite>") == 0))
                    {
                        unclosed_level4 = true;
                        level++;
                        break;
                    }
                    else if ((strcasecmp(temp7, "<p>") == 0) || (strcasecmp(temp7, "<h1>") == 0) || (strcasecmp(temp7, "<h2>") == 0) || (strcasecmp(temp7, "<h3>") == 0) || (strcasecmp(temp7, "<h4>") == 0) || (strcasecmp(temp7, "<h5>") == 0) || (strcasecmp(temp7, "<h6>") == 0) || (strcasecmp(temp7, "<ul>") == 0) || (strcasecmp(temp7, "<ol>") == 0) || (strcasecmp(temp7, "<section>") == 0))
                    {
                        unclosed_level4 = true;
                        level++;
                        break;
                    }
                    else if ((strcasecmp(temp7, "</p>") == 0) || (strcasecmp(temp7, "</h1>") == 0) || (strcasecmp(temp7, "</h2>") == 0) || (strcasecmp(temp7, "</h3>") == 0) || (strcasecmp(temp7, "</h4>") == 0) || (strcasecmp(temp7, "</h5>") == 0) || (strcasecmp(temp7, "</h6>") == 0) || (strcasecmp(temp7, "</ul>") == 0) || (strcasecmp(temp7, "</ol>") == 0) || (strcasecmp(temp7, "</section>") == 0))
                    {
                        unclosed_level4 = true;
                        level++;
                        break;
                    }
                    else if (strcasecmp(temp7, current_tag) == 0)
                    {
                        unclosed_level4 = true;
                        level++;
                        break;
                    }
                    else if ((strcasecmp(temp7, current_end_tag) == 0))
                    {
                        if (first)
            {
                current->print = false;
                current->next = NULL;
                current->prev = NULL;
                head1 = current;
                last1 = current;
                first = false;
            }
            else
            {
                newTag = (struct tag *)malloc(sizeof(struct tag));
                newTag->next = NULL;
                newTag->prev = current;
                newTag->print = true;
                current = newTag;
                    if (last1 != NULL)
                    {
                    last1->next = newTag; 
                    }
                    last1 = newTag;  
            }
            level++;
            if (attribute != NULL)
            {
                fprintf(out, "%s ", attribute);
                attribute = NULL;
            }
            temp2 = temp2->next;
            found = true;
            break;
                    }
                    else 
                    {
                        temp6 = temp6->next;
                    }
                }
                if (!found)
                {
                temp2 = temp2->next;
                unknown++;
                }
            }
            else
            {
                    fclose(out);
                        out = NULL;
                    out = fopen(fileout_name, "w");
                    fclose(out);
                        out = NULL;
                    yy = false;
                    Word_Count = false;
                    break;
            }
        }
        else if ((strcasecmp(temp2->tag, "</html>") == 0))
        {
            level = 0;
            if (unclosed_level3)
            {
                unknown--;
                unclosed_level3 = false;
                level--;
            }
            if (unclosed_level4)
            {
                unknown--;
                unclosed_level4 = false;
                level--;
            }
            fprintf(out, " ");
            if (!html_tag)
            {
             if (current != NULL)
            {
                         current = current->prev;
                         html_tag = true;   
            }
            else
            {
                html_tag = true;
                newTag = (struct tag *)malloc(sizeof(struct tag));
                newTag->next = NULL;
                newTag->prev = current;
                newTag->print = false;
                current = newTag;
                    if (last1 != NULL)
                    {
                    last1->next = newTag; 
                    }
                    last1 = newTag;  
            }
            }
            else
            {
                    fclose(out);
                        out = NULL;
                    out = fopen(fileout_name, "w");
                    fclose(out);
                        out = NULL;
                    yy = false;
                    Word_Count = false;
                    break;
            }
            temp2 = temp2->next;
        }
        else if ((strcasecmp(temp2->tag, "</title>") == 0))
        {
            fprintf(out, " ");
            if (unclosed_level3)
            {
                unknown--;
                unclosed_level3 = false;
                level--;
            }
            if (unclosed_level4)
            {
                unknown--;
                unclosed_level4 = false;
                level--;
            }
            if (level == 2)
            {
             if (current != NULL)
            {
                         current = current->prev;
                         level--;   
            }
            else
            {
                newTag = (struct tag *)malloc(sizeof(struct tag));
                newTag->next = NULL;
                newTag->prev = current;
                newTag->print = false;
                current = newTag;
                    if (last1 != NULL)
                    {
                    last1->next = newTag; 
                    }
                    last1 = newTag;
                    level--;  
            }
            }
            else
            {
                fclose(out);
                    out = NULL;
                    out = fopen(fileout_name, "w");
                    fclose(out);
                        out = NULL;
                    yy = false;
                    Word_Count = false;
                    break;
            }
            temp2 = temp2->next;
        }
        else if ((strcasecmp(temp2->tag, "</body>") == 0))
        {
            fprintf(out, " ");
            if (unclosed_level3)
            {
                unknown--;
                unclosed_level3 = false;
                level--;
            }
            if (unclosed_level4)
            {
                unknown--;
                unclosed_level4 = false;
                level--;
            }
            if (!body_tag && (level == 2))
            {
             if (current != NULL)
            {
                         current = current->prev;   
                         body_tag = true;
                         level--;
            }
            else
            {
                newTag = (struct tag *)malloc(sizeof(struct tag));
                newTag->next = NULL;
                newTag->prev = current;
                newTag->print = false;
                current = newTag;
                body_tag = true;
                level--;
                    if (last1 != NULL)
                    {
                    last1->next = newTag; 
                    }
                    last1 = newTag;  
            }
            }
            else
            {
                    fclose(out);
                        out = NULL;
                    out = fopen(fileout_name, "w");
                    fclose(out);
                        out = NULL;
                    yy = false;
                    Word_Count = false;
                    break;
            }
            temp2 = temp2->next;
        }
        else if ((strcasecmp(temp2->tag, "</p>") == 0) || (strcasecmp(temp2->tag, "</h1>") == 0) || (strcasecmp(temp2->tag, "</h2>") == 0) || (strcasecmp(temp2->tag, "</h3>") == 0) || (strcasecmp(temp2->tag, "</h4>") == 0) || (strcasecmp(temp2->tag, "</h5>") == 0) || (strcasecmp(temp2->tag, "</h6>") == 0) || (strcasecmp(temp2->tag, "</ul>") == 0) || (strcasecmp(temp2->tag, "</ol>") == 0) || (strcasecmp(temp2->tag, "</section>") == 0))
        {
            fprintf(out, " ");
            if (unclosed_level4)
            {
                unknown--;
                unclosed_level4 = false;
                level--;
            }
            if (level == 3)
            {
                if (current != NULL)
            {
                         current = current->prev;
                         level--;   
            }
            else
            {
                newTag = (struct tag *)malloc(sizeof(struct tag));
                newTag->next = NULL;
                newTag->prev = current;
                newTag->print = false;
                current = newTag;
                level--;
                    if (last1 != NULL)
                    {
                    last1->next = newTag; 
                    }
                    last1 = newTag;  
            }
            }
            else
            {
                fclose(out);
                    out = NULL;
                    out = fopen(fileout_name, "w");
                    fclose(out);
                        out = NULL;
                    yy = false;
                    Word_Count = false;
                    break;
            }
            temp2 = temp2->next;
        }
        else if ((strcasecmp(temp2->tag, "</li>") == 0) || (strcasecmp(temp2->tag, "</b>") == 0) || (strcasecmp(temp2->tag, "</i>") == 0) || (strcasecmp(temp2->tag, "</strong>") == 0) || (strcasecmp(temp2->tag, "</em>") == 0) || (strcasecmp(temp2->tag, "</small>") == 0) || (strcasecmp(temp2->tag, "</code>") == 0) || (strcasecmp(temp2->tag, "</pre>") == 0) || (strcasecmp(temp2->tag, "</sub>") == 0) || (strcasecmp(temp2->tag, "</sup>") == 0) || (strcasecmp(temp2->tag, "</a>") == 0) || (strcasecmp(temp2->tag, "</label>") == 0) || (strcasecmp(temp2->tag, "</abbr>") == 0) || (strcasecmp(temp2->tag, "</addr>") == 0) || (strcasecmp(temp2->tag, "</q>") == 0) || (strcasecmp(temp2->tag, "</blockquote>") == 0) || (strcasecmp(temp2->tag, "</div>") == 0) || (strcasecmp(temp2->tag, "</cite>") == 0))
        {
            fprintf(out, " ");
            if (level == 4)
            {
                if (current != NULL)
            {
                         current = current->prev;
                         level--;   
            }
            else
            {
                newTag = (struct tag *)malloc(sizeof(struct tag));
                newTag->next = NULL;
                newTag->prev = current;
                newTag->print = false;
                current = newTag;
                level--;
                    if (last1 != NULL)
                    {
                    last1->next = newTag; 
                    }
                    last1 = newTag;  
            }
            } 
            else
            {
                fclose(out);
                    out = NULL;
                    out = fopen(fileout_name, "w");
                    fclose(out);
                        out = NULL;
                    yy = false;
                    Word_Count = false;
                    break;
            }
            temp2 = temp2->next;
        }
        else if ((strstr(temp2->tag, "<") != NULL) && (strstr(temp2->tag, ">") != NULL) && (strstr(temp2->tag, "/") != NULL) && (strlen(strstr(temp2->tag, "/")) == (strlen(strstr(temp2->tag, "<")) - 1 )))
        {
            fprintf(out, " ");
            if (current != NULL)
            {
                         current = current->prev;
                         level--;   
            }
            else
            {
                newTag = (struct tag *)malloc(sizeof(struct tag));
                newTag->next = NULL;
                newTag->prev = current;
                newTag->print = false;
                current = newTag;
                level--; 
                    if (last1 != NULL)
                    {
                    last1->next = newTag; 
                    }
                    last1 = newTag;  
            }
            temp2 = temp2->next;
        }
        else if ((strstr(temp2->tag, "<") != NULL) && (strstr(temp2->tag, ">") != NULL))
        {
            if (strstr(temp2->tag, " ") != NULL)
            {
                char *temp = malloc(strlen(temp2->tag) * 10);
                free(temp);
                temp = substring(temp2->tag, 1, strlen(temp2->tag) - strlen(strstr(temp2->tag, " ")));
                if ((strcasecmp(temp, "<html") == 0) || (strcasecmp(temp, "<title") == 0) || (strcasecmp(temp, "<body") == 0) || (strcasecmp(temp, "<p") == 0) || (strcasecmp(temp, "<h1") == 0) || (strcasecmp(temp, "<h2") == 0) || (strcasecmp(temp, "<h3") == 0) || (strcasecmp(temp, "<h4") == 0) || (strcasecmp(temp, "<h5") == 0) || (strcasecmp(temp, "<h6") == 0) || (strcasecmp(temp, "<li") == 0) || (strcasecmp(temp, "<ul") == 0) || (strcasecmp(temp, "<ol") == 0) || (strcasecmp(temp, "<b") == 0) || (strcasecmp(temp, "<i") == 0) || (strcasecmp(temp, "<strong") == 0) || (strcasecmp(temp, "<em") == 0) || (strcasecmp(temp, "<small") == 0) || (strcasecmp(temp, "<code") == 0) || (strcasecmp(temp, "<pre") == 0) || (strcasecmp(temp, "<sub") == 0) || (strcasecmp(temp, "<sup") == 0) || (strcasecmp(temp, "<a") == 0) || (strcasecmp(temp, "<label") == 0) || (strcasecmp(temp, "<abbr") == 0) || (strcasecmp(temp, "<addr") == 0) || (strcasecmp(temp, "<q") == 0) || (strcasecmp(temp, "<blockquote") == 0) || (strcasecmp(temp, "<div") == 0) || (strcasecmp(temp, "<cite") == 0) || (strcasecmp(temp, "<section") == 0))
                {
                    if (mystristr(temp2->tag, " title=") != NULL)
                    {
                        char *temp3 = malloc(strlen(temp2->tag) * 10);
                        free(temp3);
                        temp3 = mystristr(temp2->tag, " title=");
                        int zz = 0;
                        int z = 0;
                        for (int i = 0; i < strlen(temp3); i++)
                        {
                            if ((temp3[i] == '"') && (zz == 0))
                            {
                                zz = i;
                            }
                            else if (temp3[i] == '"')
                            {
                                z = i;
                                break;
                            }
                        }
                        attribute = substring(temp3, zz + 2, z - zz - 1);
                    }
            temp2->tag = strcat(temp, ">");
                }
                else
                {
                    bool found = false;
                int current_recognized_tags = 0;
                int tag = 0;
                struct node *temp6 = temp2->next;
                char *current_tag = substring(temp2->tag, 1, strlen(temp2->tag) - strlen((strstr(temp2->tag, " "))));
                current_tag = strcat(current_tag, ">");
                char *current_end_tag = strcat(substring(current_tag, 1, 1), "/");
                current_end_tag = strcat(current_end_tag, substring(current_tag, 2,strlen(current_tag)));
                while (temp6 != NULL)
                {
                    char *temp7 = temp6->tag;
                    if ((strstr(temp7, "<") != NULL) && (strstr(temp7, ">") != NULL) && (strstr(temp7, " ") != NULL))
                    {
                        temp7 = substring(temp7, 1, strlen(temp7) - strlen((strstr(temp7, " "))));
                        temp7 = strcat(temp7, ">");
                    }
                    if ((strcasecmp(temp7, "<html>") == 0) || (strcasecmp(temp7, "<title>") == 0) || (strcasecmp(temp7, "<body>") == 0) || (strcasecmp(temp7, "<p>") == 0) || (strcasecmp(temp7, "<h1>") == 0) || (strcasecmp(temp7, "<h2>") == 0) || (strcasecmp(temp7, "<h3>") == 0) || (strcasecmp(temp7, "<h4>") == 0) || (strcasecmp(temp7, "<h5>") == 0) || (strcasecmp(temp7, "<h6>") == 0) || (strcasecmp(temp7, "<li>") == 0) || (strcasecmp(temp7, "<ul>") == 0) || (strcasecmp(temp7, "<ol>") == 0) || (strcasecmp(temp7, "<b>") == 0) || (strcasecmp(temp7, "<i>") == 0) || (strcasecmp(temp7, "<strong>") == 0) || (strcasecmp(temp7, "<em>") == 0) || (strcasecmp(temp7, "<small>") == 0) || (strcasecmp(temp7, "<code>") == 0) || (strcasecmp(temp7, "<pre>") == 0) || (strcasecmp(temp7, "<sub>") == 0) || (strcasecmp(temp7, "<sup>") == 0) || (strcasecmp(temp7, "<a>") == 0) || (strcasecmp(temp7, "<label>") == 0) || (strcasecmp(temp7, "<abbr>") == 0) || (strcasecmp(temp7, "<addr>") == 0) || (strcasecmp(temp7, "<q>") == 0) || (strcasecmp(temp7, "<blockquote>") == 0) || (strcasecmp(temp7, "<div>") == 0) || (strcasecmp(temp7, "<cite>") == 0) || (strcasecmp(temp7, "<section>") == 0))
                    {
                        current_recognized_tags = current_recognized_tags + 1;
                        temp6 = temp6->next;
                    }
                    else if (((strcasecmp(temp7, "</html>") == 0) || (strcasecmp(temp7, "</title>") == 0) || (strcasecmp(temp7, "</body>") == 0) || (strcasecmp(temp7, "</p>") == 0) || (strcasecmp(temp7, "</h1>") == 0) || (strcasecmp(temp7, "</h2>") == 0) || (strcasecmp(temp7, "</h3>") == 0) || (strcasecmp(temp7, "</h4>") == 0) || (strcasecmp(temp7, "</h5>") == 0) || (strcasecmp(temp7, "</h6>") == 0) || (strcasecmp(temp7, "</li>") == 0) || (strcasecmp(temp7, "</ul>") == 0) || (strcasecmp(temp7, "</ol>") == 0) || (strcasecmp(temp7, "</b>") == 0) || (strcasecmp(temp7, "</i>") == 0) || (strcasecmp(temp7, "</strong>") == 0) || (strcasecmp(temp7, "</em>") == 0) || (strcasecmp(temp7, "</small>") == 0) || (strcasecmp(temp7, "</code>") == 0) || (strcasecmp(temp7, "</pre>") == 0) || (strcasecmp(temp7, "</sub>") == 0) || (strcasecmp(temp7, "</sup>") == 0) || (strcasecmp(temp7, "</a>") == 0) || (strcasecmp(temp7, "</label>") == 0) || (strcasecmp(temp7, "</abbr>") == 0) || (strcasecmp(temp7, "</addr>") == 0) || (strcasecmp(temp7, "</q>") == 0) || (strcasecmp(temp7, "</blockquote>") == 0) || (strcasecmp(temp7, "</div>") == 0) || (strcasecmp(temp7, "</cite>") == 0) || (strcasecmp(temp7, "</section>") == 0)) && (current_recognized_tags == 0))
                    {
                        temp2 = temp2->next;
                        found = true;
                        break;
                    }
                    else if ((strcasecmp(temp7, "</html>") == 0) || (strcasecmp(temp7, "</title>") == 0) || (strcasecmp(temp7, "</body>") == 0) || (strcasecmp(temp7, "</p>") == 0) || (strcasecmp(temp7, "</h1>") == 0) || (strcasecmp(temp7, "</h2>") == 0) || (strcasecmp(temp7, "</h3>") == 0) || (strcasecmp(temp7, "</h4>") == 0) || (strcasecmp(temp7, "</h5>") == 0) || (strcasecmp(temp7, "</h6>") == 0) || (strcasecmp(temp7, "</li>") == 0) || (strcasecmp(temp7, "</ul>") == 0) || (strcasecmp(temp7, "</ol>") == 0) || (strcasecmp(temp7, "</b>") == 0) || (strcasecmp(temp7, "</i>") == 0) || (strcasecmp(temp7, "</strong>") == 0) || (strcasecmp(temp7, "</em>") == 0) || (strcasecmp(temp7, "</small>") == 0) || (strcasecmp(temp7, "</code>") == 0) || (strcasecmp(temp7, "</pre>") == 0) || (strcasecmp(temp7, "</sub>") == 0) || (strcasecmp(temp7, "</sup>") == 0) || (strcasecmp(temp7, "</a>") == 0) || (strcasecmp(temp7, "</label>") == 0) || (strcasecmp(temp7, "</abbr>") == 0) || (strcasecmp(temp7, "</addr>") == 0) || (strcasecmp(temp7, "</q>") == 0) || (strcasecmp(temp7, "</blockquote>") == 0) || (strcasecmp(temp7, "</div>") == 0) || (strcasecmp(temp7, "</cite>") == 0) || (strcasecmp(temp7, "</section>") == 0))
                    {
                        current_recognized_tags = current_recognized_tags - 1;
                        temp6 = temp6->next;
                    }
                    else if (strcasecmp(temp7, current_tag) == 0)
                    {
                        tag = tag + 1;
                        temp6 = temp6->next;
                    }
                    else if ((strcasecmp(temp7, current_end_tag) == 0) && (tag == 0))
                    {
                        if (first)
            {
                current->print = false;
                current->next = NULL;
                current->prev = NULL;
                head1 = current;
                last1 = current;
                first = false;
            }
            else
            {
                newTag = (struct tag *)malloc(sizeof(struct tag));
                newTag->next = NULL;
                newTag->prev = current;
                newTag->print = false;
                current = newTag;
                level++;
                if (last1 != NULL)
                    {
                    last1->next = newTag; 
                    }
                    last1 = newTag;   
            }
            temp2 = temp2->next;
            found = true;
            break;
                    }
                    else if ((strcasecmp(temp7, current_end_tag) == 0))
                    {
                        tag = tag - 1;
                        temp6 = temp6->next;
                    }
                    else 
                    {
                        temp6 = temp6->next;
                    }
                }
                if (!found)
                {
                temp2 = temp2->next;
                }
                }
            }
            else
            {
                bool found = false;
                int current_recognized_tags = 0;
                int tag = 0;
                struct node *temp6 = temp2->next;
                char *current_tag = temp2->tag;
                char *current_end_tag = malloc(strlen(temp2->tag) * 100);
                free(current_end_tag);
                current_end_tag = strcat(substring(current_tag, 1, 1), "/");
                current_end_tag = strcat(current_end_tag, substring(current_tag, 2,strlen(current_tag)));
                while (temp6 != NULL)
                {
                    char *temp7 = temp6->tag;
                    if ((strstr(temp7, "<") != NULL) && (strstr(temp7, ">") != NULL) && (strstr(temp7, " ") != NULL))
                    {
                        temp7 = substring(temp7, 1, strlen(temp7) - strlen((strstr(temp7, " "))));
                        temp7 = strcat(temp7, ">");
                    }
                    if ((strcasecmp(temp7, "<p>") == 0) || (strcasecmp(temp7, "<h1>") == 0) || (strcasecmp(temp7, "<h2>") == 0) || (strcasecmp(temp7, "<h3>") == 0) || (strcasecmp(temp7, "<h4>") == 0) || (strcasecmp(temp7, "<h5>") == 0) || (strcasecmp(temp7, "<h6>") == 0) || (strcasecmp(temp7, "<li>") == 0) || (strcasecmp(temp7, "<ul>") == 0) || (strcasecmp(temp7, "<ol>") == 0) || (strcasecmp(temp7, "<b>") == 0) || (strcasecmp(temp7, "<i>") == 0) || (strcasecmp(temp7, "<strong>") == 0) || (strcasecmp(temp7, "<em>") == 0) || (strcasecmp(temp7, "<small>") == 0) || (strcasecmp(temp7, "<code>") == 0) || (strcasecmp(temp7, "<pre>") == 0) || (strcasecmp(temp7, "<sub>") == 0) || (strcasecmp(temp7, "<sup>") == 0) || (strcasecmp(temp7, "<a>") == 0) || (strcasecmp(temp7, "<label>") == 0) || (strcasecmp(temp7, "<abbr>") == 0) || (strcasecmp(temp7, "<addr>") == 0) || (strcasecmp(temp7, "<q>") == 0) || (strcasecmp(temp7, "<blockquote>") == 0) || (strcasecmp(temp7, "<div>") == 0) || (strcasecmp(temp7, "<cite>") == 0) || (strcasecmp(temp7, "<section>") == 0))
                    {
                        current_recognized_tags = current_recognized_tags + 1;
                        temp6 = temp6->next;
                    }
                    else if ((strcasecmp(temp7, "</html>") == 0) || (strcasecmp(temp7, "</title>") == 0) || (strcasecmp(temp7, "</body>") == 0))
                    {
                        found = false;
                        break;
                    }
                    else if ((strcasecmp(temp7, "</p>") == 0) || (strcasecmp(temp7, "</h1>") == 0) || (strcasecmp(temp7, "</h2>") == 0) || (strcasecmp(temp7, "</h3>") == 0) || (strcasecmp(temp7, "</h4>") == 0) || (strcasecmp(temp7, "</h5>") == 0) || (strcasecmp(temp7, "</h6>") == 0) || (strcasecmp(temp7, "</li>") == 0) || (strcasecmp(temp7, "</ul>") == 0) || (strcasecmp(temp7, "</ol>") == 0) || (strcasecmp(temp7, "</b>") == 0) || (strcasecmp(temp7, "</i>") == 0) || (strcasecmp(temp7, "</strong>") == 0) || (strcasecmp(temp7, "</em>") == 0) || (strcasecmp(temp7, "</small>") == 0) || (strcasecmp(temp7, "</code>") == 0) || (strcasecmp(temp7, "</pre>") == 0) || (strcasecmp(temp7, "</sub>") == 0) || (strcasecmp(temp7, "</sup>") == 0) || (strcasecmp(temp7, "</a>") == 0) || (strcasecmp(temp7, "</label>") == 0) || (strcasecmp(temp7, "</abbr>") == 0) || (strcasecmp(temp7, "</addr>") == 0) || (strcasecmp(temp7, "</q>") == 0) || (strcasecmp(temp7, "</blockquote>") == 0) || (strcasecmp(temp7, "</div>") == 0) || (strcasecmp(temp7, "</cite>") == 0) || (strcasecmp(temp7, "</section>") == 0))
                    {
                        current_recognized_tags = current_recognized_tags - 1;
                        temp6 = temp6->next;
                    }
                    else if (strcasecmp(temp7, current_tag) == 0)
                    {
                        tag = tag + 1;
                        temp6 = temp6->next;
                    }
                    else if ((strcasecmp(temp7, current_end_tag) == 0) && (tag == 0))
                    {
                        level++;
                        if (first)
            {
                current->print = false;
                current->next = NULL;
                current->prev = NULL;
                head1 = current;
                last1 = current;
                first = false;
            }
            else
            {
                newTag = (struct tag *)malloc(sizeof(struct tag));
                newTag->next = NULL;
                newTag->prev = current;
                newTag->print = false;
                current = newTag;
                if (last1 != NULL)
                    {
                    last1->next = newTag; 
                    }
                    last1 = newTag;   
            }
            temp2 = temp2->next;
            found = true;
            break;
                    }
                    else if ((strcasecmp(temp7, current_end_tag) == 0))
                    {
                        tag = tag - 1;
                        temp6 = temp6->next;
                    }
                    else 
                    {
                        temp6 = temp6->next;
                    }
                }
                if (!found)
                {
                temp2 = temp2->next;
                }
            }
        }
        else
        {
            if (unknown == 0)
            {
            if (current != NULL)
            {
           print_current = current->print;
            }
            else
            {
                print_current = false;
                fprintf(out, "\n");
            }
            if (print_current)
            {
                fprintf(out, "%s", temp2->tag);
            }
            else
            {
                bool add = true;
                for (int i = 0; i < strlen(temp2->tag); i++)
                {
                    if (!isspace(temp2->tag[i]))
                    {
                        add = false;
                        break;
                    }
                }
                if (add)
                {
                    fprintf(out, "%s", temp2->tag);
                }
            }
            }
            else
            {
                bool add = true;
                for (int i = 0; i < strlen(temp2->tag); i++)
                {
                    if (!isspace(temp2->tag[i]))
                    {
                        add = false;
                        break;
                    }
                }
                if (add)
                {
                    fprintf(out, "%s", temp2->tag);
                }
            }
            temp2 = temp2->next;
        }
    }
    fclose(in);
    if (out != NULL)
    {
    fclose(out);
    out = NULL;
    }
    if (!html_tag)
    {
                    out = fopen(fileout_name, "w");
                    fclose(out);
                    out = NULL;
                    yy = false;
                    Word_Count = false;
    }
    else if (!body_tag)
    {
                    out = fopen(fileout_name, "w");
                    fclose(out);
                    out = NULL;
                    yy = false;
                    Word_Count = false;
    }
    char list[400][1024];
    char line2[1024];
    if (Word_Count)
    {
        out = fopen(fileout_name, "r");
        int X = 0;
            char w[200][1024];
            while (fscanf(out, "%s", line2) != EOF)
        {
            int XX = 0;
            for (int i = 0; i < strlen(line2); i++)
            {
                if (isalnum(line2[i]))
                {
                    w[X][XX] = line2[i];
                    XX++;
                }
                else
                {
                    XX = 0;
                    X++;
                }
            }
             X++;
        }
        int Y = 0;
        for (int i = 0; i < X; i++)
            {
                bool add = true;
                for (int k = 0; k < Y; k++)
                {
                    if (strcasecmp(list[k], w[i]) == 0)
                    {
                        add = false;
                        break;
                    }
                    else if (strlen(w[i]) == 0)
                    {
                        add = false;
                        break;
                    }
                }
                if (add)
                {
                    strcpy(list[Y], w[i]);
                    Y++;
                    word_count++;
                }
            }
     fclose(out);
     out = NULL;   
    }
    if (find_frequency != NULL)
        {
            out = fopen(fileout_name, "r");
            rewind(out);
            int X = 0;
            char w[200][1024];
            while (fscanf(out, "%s", line2) != EOF)
        {
            int XX = 0;
            for (int i = 0; i < strlen(line2); i++)
            {
                if (isalnum(line2[i]))
                {
                    w[X][XX] = line2[i];
                    XX++;
                }
                else
                {
                    XX = 0;
                    X++;
                }
            }
             X++;
        }
        for (int i = 0; i < X; i++)
            {
                if (strcasecmp(w[i], find_frequency) == 0)
            {
                specific_word_count++;
            }
            }
            fclose(out);
            out = NULL;
        }
    if (Word_Count)
    {
        if (yy)
        {
        printf("Word Count: %d.", word_count);
        }
        else
        {
            printf("Word Count: %d.\n", word_count);
        }
    }
    if (yy)
    {
    if (find_frequency != NULL)
        {
            char n[strlen(find_frequency) + 1];
            strcpy(n, find_frequency);
            for (int i = 0; i < strlen(n); i++)
            {
                n[i] = tolower(n[i]);
            }
            n[0] = toupper(n[0]);
            if (word_count)
            {
                printf(" %s Frequency: %d.\n", n, specific_word_count);
            }
            else
            {
                printf("%s Frequency: %d.\n", n, specific_word_count);
            }
            
        }
    }
    while (head != NULL)
    {
        struct node *t = head->next;
        if ((strcmp(head->tag, "\n") != 0) && (head->tag == NULL))
        {
        free(head->tag);
        }
        free(head);
        head = t;
    }
    while (first1 != NULL)
    {
        struct list *t = first1->next;
        if ((first1->words != NULL))
        {
        free(first1->words);
         first1->words = NULL;
        }
        free(first1);
        first1 = t;
    } 
        while (head1 != NULL)
    {
        struct tag *t = head1->next;
        free(head1);
        head1 = NULL;
        head1 = t;
    }
    return(1);
}