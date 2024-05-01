/*Startup for cortex m3*/

.section .vectors

.word 0x20001000 /*stack top adress*/
.word _reset
.word vector_handler       /*NMI*/
.word vector_handler       /*HARD FAULT*/
.word vector_handler       /*MM FAULT*/
.word vector_handler       /*BUS FAULT*/
.word vector_handler       /*USAGE FAULT*/
.word vector_handler       /*RESERVED*/
.word vector_handler       /*RESERVED*/
.word vector_handler       /*RESERVED*/
.word vector_handler       /*RESERVED*/
.word vector_handler       /*SV CALL*/
        /*ETC to reach all intrrupt vectors*/

 .section .text
 _reset:
     bl main
     b .

 .thumb_func
 vector_handler:
     b _reset