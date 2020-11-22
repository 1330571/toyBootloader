waitforkey: 
    pusha 

    xor ah,ah 
    int 0x16

    popa 
    ret