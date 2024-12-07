#include <stdio.h> 
#include <string.h> 
#include <ctype.h> 
#include <stdlib.h> 
// structure used to define a node 
typedef struct node_t 
{ 
struct node_t *left, *right; 
int freq; 
char c; 
} *node; 
// global variables 
int n_nodes = 0, qend = 1; 
// global variables for keep track of no.of nodes and end 
of the que 
struct node_t pool[256] = {{0}}; // pool of nodes 
node qqq[255], *q = qqq - 1; // the priority que 
char *code[128] = {0}, buf[1024]; // a string array of the codes for each letter 
int input_data = 0, output_data = 0; 
// function used to create a new node 
node new_node(int freq, char c, node a, node b) 
{ 
node n = pool + n_nodes++; 
if (freq != 0) 
{ 
n->c = c; 
// assign the character 'c' to the character of the node (eventually a leaf) 
n->freq = freq; // assign frequency 
} 
else 
7 
{ 
n->left = a, n->right = b; // if there is no frequency provided with the invoking 
n->freq = a->freq + b->freq; // the removed nodes at the end of the que will be 
added to left and right 
} 
return n; 
} 
// function ued to insert a node into the priority que 
void qinsert(node n) 
{ 
} 
int j, i = qend++; 
while ((j = i / 2)) 
{ 
if (q[j]->freq <= n->freq) 
break; 
q[i] = q[j], i = j; 
} 
q[i] = n; 
node qremove() 
{ 
int i, l; 
node n = q[i = 1]; 
if (qend < 2) 
return 0; 
qend--; 
while ((l = i * 2) < qend) 
{ 
if (l + 1 < qend && q[l + 1]->freq < q[l]->freq) 
l++; 
q[i] = q[l], i = l; 
} 
q[i] = q[qend]; 
return n; // return the node 
} 
// go along the builded huffman tree and assign the code for each character 
void build_code(node n, char *s, int len) 
{ 
static char *out = buf; 
if (n->c) 
{ 
} 
s[len] = 0; 
strcpy(out, s);  
// if the provided node is a leaf (end node) 
// it contains a character 
code[(int)n->c] = out; // therefore the code is copied into the relevant character. 
out += len + 1; 
// out pointer is incremented 
return; 
s[len] = '0'; 
build_code(n->left, s, len + 1); // recurring is used to write out the code 
s[len] = '1'; 
build_code(n->right, s, len + 1); // if right add a 1 and if right add a 0 
} 
void import_file(FILE *fp_in, unsigned int *freq, const char *file_name) 
{ 
char c, s[16] = {0}; // temporary variables 
int i = 0; 
// Reset input_data to 0 before reading the file 
input_data = 0; 
while ((c = fgetc(fp_in)) != EOF) 
{ 
freq[(int)c]++; // read the file character by character and increment the particular 
frequency 
input_data++; // update input_data for each character read 
} 

// Save the frequency table to a separate table file with the same base name as the input 
file 
char table_filename[50]; 
sprintf(table_filename, "%s.huffman.table", file_name); 
FILE *fp_table_out = fopen(table_filename, "w"); 
for (i = 0; i < 128; i++) 
{ 
if (freq[i] != 0) 
{ 
fprintf(fp_table_out, "%d %d\n", i, freq[i]); 
} 
} 
fclose(fp_table_out); 
for (i = 0; i < 128; i++) 
if (freq[i]) 
qinsert(new_node(freq[i], i, 0, 0)); // insert new nodes into the que if there is a 
frequency 
while (qend > 2) 
qinsert(new_node(0, 0, qremove(), qremove())); // build the tree 
build_code(q[1], s, 0); 
// build the code for the characters 
} 
void encode(FILE *fp_in, FILE *fp_out, unsigned int *freq, const char *file_name) 
{ 
char in, temp[20] = {0}; 
int i, j = 0, k = 0, lim = 0; 
unsigned char c = 0; // Use an unsigned char for precise bit manipulation 
rewind(fp_in); 
// Reset output_data to 0 before encoding 
output_data = 0; 
for (i = 0; i < 128; i++) 
{ 
if (freq[i]) 
lim += (freq[i] * strlen(code[i])); 
} 
fprintf(fp_out, "%04d\n", lim); 
for (i = 0; i < lim; i++) 
{ 
if (temp[j] == '\0') 
{ 
in = fgetc(fp_in); 
strcpy(temp, code[in]); 
j = 0; 
} 
if (temp[j] == '1') 
c |= (1 << (7 - k)); 
else if (temp[j] == '0') 
c |= (0 << (7 - k)); 
else 
printf("ERROR: Wrong input!\n"); 
k++; 
j++; 
if (((i + 1) % 8 == 0) || (i == lim - 1)) 
{ 
k = 0; 
fputc(c, fp_out); 
c = 0; 
output_data++; 
} 
} 
} 
void print_code(unsigned int *freq) 
{ 
int i; 
printf("\n\n**************"); 
printf("\n 
CHAR FREQ TABLE"); 
11 
printf("\n**************\n"); 
for (i = 0; i < 128; i++) 
{ 
if (isprint((char)i) && code[i] != NULL && i != ' ') 
printf("%-4c %-4d %16s\n", i, freq[i], code[i]); 
else if (code[i] != NULL) 
{ 
switch (i) 
{ 
case '\n': 
printf("\\n "); 
break; 
case ' ': 
printf("\' \' "); 
break; 
case '\t': 
printf("\\t "); 
break; 
default: 
printf("%0X ", (char)i); 
break; 
} 
printf(" %-4d %16s\n", freq[i], code[i]); 
} 
} 
printf("\n**************"); 
} 
void import_table(FILE *fp_table, unsigned int *freq) 
{ 
int character, frequency; 
while (fscanf(fp_table, "%d %d", &character, &frequency) == 2) 
{ 
freq[character] = frequency; 
} 
} 
void decode(FILE *fp_huffman, FILE *fp_out, unsigned int *freq) 
{ 
int lim = 0; 
char c; 
node n = q[1]; 
// Read the length of the bit stream from the header 
fscanf(fp_huffman, "%d", &lim); 
// Skip the header until a newline character is encountered 
while (fgetc(fp_huffman) != '\n') 
; 
for (int i = 0; i < lim; i++) 
{ 
int bit = fgetc(fp_huffman); 
if (bit == EOF) 
{ 
break; 
} 
for (int j = 7; j >= 0; j--) 
{ 
if (bit & (1 << j)) 
n = n->right; 
else 
n = n->left; 
if (n->c) 
{ 
fputc(n->c, fp_out); 
n = q[1]; 
freq[(int)n->c]++; 
} 
} 
} 
putchar('\n'); 
} 
int main(int argc, char *argv[]) 
{ 
FILE *fp_in, *fp_out, *fp_huffman; // File pointers 
char file_name[50] = {0}; 
unsigned int freq[128] = {0}; 
int choice, i; 
system("cls"); 
// File name 
// Frequency of the letters 
printf("*******************************\n"); 
printf(" 
Data Structures PBL\n"); 
printf(" 
printf("  
Akshit | Saiteja | Harshith\n"); --HUFFMAN ENCODER--\n"); 
printf("*******************************\n\n"); 
while (1) 
{ 
printf("\n\nMenu:\n"); 
printf("1. Compress\n"); 
printf("2. Decompress\n"); 
printf("3. Exit\n"); 
printf("Enter your choice: "); 
scanf("%d", &choice); 
switch (choice) 
{ 
case 1: 
// Compression 
if (argc == 2) 
{ 
strcpy(file_name, argv[1]); // Command-line argument directly allows 
compressing the file 
} 
else if (argc > 2) 
{ 
printf("Too many arguments supplied.\n"); 
continue; 
} 
else 
{ 
printf("Please enter the file to be compressed: "); 
scanf("%s", file_name); 
} 
if (strlen(file_name) >= 50) 
{ 
printf("ERROR: Enter a file name less than 50 chars\n"); 
continue; 
} 
// Import the file into the program and update the Huffman tree 
if ((fp_in = fopen(file_name, "r")) == NULL) 
{ 
printf("\nERROR: No such file\n"); 
continue; 
} 
import_file(fp_in, freq, file_name); // Import the file and fill the frequency array 
print_code(freq); 
// Print the code table 
// Encode and save the encoded file 
strcat(file_name, ".huffman"); // Encoded file is saved in .huffman extension 
fp_out = fopen(file_name, "w"); 
encode(fp_in, fp_out, freq, file_name); 
fclose(fp_in); 
fclose(fp_out); 
// Display compression details 
printf("\nInput bytes: %d\n", input_data); 
printf("Output bytes: %d\n", output_data); 
// Calculate and display compression ratio 
double compression_ratio = ((double)(input_data - output_data) / input_data) * 
100; 
printf("Compression ratio: %.2f%%", compression_ratio); 
printf("\n**************\n"); 
printf("\nCompression complete. Encoded file saved as %s\n\n", file_name); 
break; 
// ... (remaining code remains unchanged) 
case 2: 
// Decompression 
printf("Enter the compressed file name: "); 
scanf("%s", file_name); 
// Decompression code 
fp_huffman = fopen(file_name, "r"); 
if (fp_huffman == NULL) 
{ 
printf("\nERROR: Compressed file not found\n"); 
continue; 
} 
// Read the frequency table from the header 
char table_filename[50]; 
sprintf(table_filename, "%s.table", file_name); 
FILE *fp_table = fopen(table_filename, "r"); 

if (fp_table == NULL) 
{ 
printf("\nERROR: Frequency table file not found\n"); 
fclose(fp_huffman); 
continue; 
} 
import_table(fp_table, freq); 
fclose(fp_table); 
// Rebuild the Huffman tree 
while (qend > 2) 
qinsert(new_node(0, 0, qremove(), qremove())); 
// Create a new output file for the decompressed data 
char decompressed_file_name[50]; 
sprintf(decompressed_file_name, "decompressed_%s", file_name); 
fp_out = fopen(decompressed_file_name, "w"); 
if (fp_out == NULL) 
{ 
printf("\nERROR: Cannot create decompressed file\n"); 
fclose(fp_huffman); 
continue; 
} 
// Decode and save the decompressed file 
decode(fp_huffman, fp_out, freq); 
fclose(fp_huffman); 
fclose(fp_out); 
printf("\nDecompression complete. Decoded file saved as %s\n\n", 
decompressed_file_name); 
break; 
case 3: 
// Exit 
printf("Exiting the program.\n"); 
return 0; 
default: 
printf("Invalid choice. Please enter a valid option.\n"); 
break; 
} 
} 
retu
