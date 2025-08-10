function wn_main (){
    wn_fs_newFile ("example.txt");
    wn_fs_openFile("example.txt");
    wn_fs_writeFile("Hello from the example.txt");
    wn_fs_readFile ();
    wn_continue (()=>{
        if (wn_fs_readFileBuffer != ""){
            alert (`The file data is : ${wn_normalize(wn_fs_readFileBuffer)}`);
            wn_fs_readFileBase64();
            wn_continue (()=>{
                if (wn_fs_readFileBuffer != ""){
                    alert (`The file data is : ${wn_fs_readFileBuffer}`);
                }
            })
        }
    })
}