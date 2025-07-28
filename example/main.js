function wn_main (){
    wn_fs_newFile ("example.txt");
    wn_fs_openFile("example.txt");
    wn_fs_writeFile("Hello from the example.txt");
    wn_fs_closeFile();
}