#include <stdio.h>

static void table_begin(void);
static void table_end(void);
static void header_row_begin(void);
static void header_row_end(void);
static void row_begin(void);
static void row_end(void);
static void header_col_begin(void);
static void header_col_end(void);
static void col_begin(void);
static void col_end(void);

#define TRUE            (1)
#define FALSE           (0)

#define ROW_SEPERATOR   ('\n')
#define COL_SEPERATOR   (',')

int main(int argc, char* argv)
{
   int c;
   int col_started   = FALSE;
   int row_started   = FALSE;
   int header_row    = TRUE;

   table_begin();

   while((c = getc(stdin)) != EOF)
   {
      if (COL_SEPERATOR == c)
      {
         if (row_started)
         {
            if (col_started)
            {
               if (header_row)
               {
                  header_col_end();
               }
               else
               {
                  col_end();
               }
               col_started = FALSE;
            }
            else
            {
               if (header_row)
               {
                  header_col_begin();
                  header_col_end();
               }
               else
               {
                  col_begin();
                  col_end();
               }
            }
         }
         else
         {
            if (header_row)
            {
               header_row_begin();
            }
            else
            {
               row_begin();
            }
            row_started = TRUE;
         }
      }
      else if (ROW_SEPERATOR == c)
      {
         if (col_started)
         {
            if (header_row)
            {
               header_col_end();
            }
            else
            {
               col_end();
            }
         }

         if (header_row)
         {
            header_row_end();
            header_row = FALSE;
         }
         else
         {
            row_end();
         }

         row_started = FALSE;
         col_started = FALSE;
      }
      else
      {
         if (!row_started)
         {
            if (header_row)
            {
               header_row_begin();
               if (!col_started)
               {
                  header_col_begin();
               }
            }
            else
            {
               row_begin();
               if (!col_started)
               {
                  col_begin();
               }
            }

            row_started = TRUE;
            col_started = TRUE;
         }
         else if (!col_started)
         {
            if(header_row)
            {
               header_col_begin();
            }
            else
            {
               col_begin();
            }
            col_started = TRUE;
         }

         putc(c, stdout);
      }
   }

   if (col_started)
   {
      if (header_row)
      {
         header_col_end();
      }
      else
      {
         col_end();
      }
   }

   if (header_row)
   {
      header_row_end();
   }
   else
   {
      row_end();
   }

   table_end();
}

static void table_begin(void)
{
   printf("{| class=\"wikitable\"\n");
}

static void table_end(void)
{
   printf("|}\n");
}

static void header_row_begin(void)
{
   printf("|-\n");
}

static void header_row_end(void)
{
}

static void row_begin(void)
{
   printf("|-\n");
}

static void row_end(void)
{
}

static void col_begin(void)
{
   putc('|', stdout);
}

static void col_end(void)
{
   putc('\n', stdout);
}

static void header_col_begin(void)
{
   putc('!', stdout);
}

static void header_col_end(void)
{
   putc('\n', stdout);
}
