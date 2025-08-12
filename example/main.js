function mkfile (){
    wn_fs_newFile ("eg/example.txt");
    wn_fs_openFile("eg/example.txt");
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
function wn_main (){
    wn_set_dataDir("com.eg.wn")
    wn_fs_isDirExists("eg");
    wn_continue(()=>{
        if (wn_fs_isDirExistsBuffer){
            alert ("dir exists");
            mkfile();
            // wn_fs_remove ("eg");
            wn_system_piped ("ls");
            wn_continue (()=>{
                alert (wn_normalize(wn_system_pipedBuffer));
            })
        }
        else {
            alert ("dir dont exists");
            wn_fs_newDir("eg");
            mkfile();
        }
    });
}