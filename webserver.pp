program webserver;
{ Credit goes to https://github.com/PierceNg/wasm-demo. }

uses
    {$ifdef unix}cmem, cthreads,{$endif}
    classes, fphttpapp, fpwebfile;

begin
    GetDir(0, TSimpleFileModule.BaseDir);
    TSimpleFileModule.RegisterDefaultRoute;
    TSimpleFileModule.IndexPageName := 'index.html';
    MimeTypesFile := 'mime.types';

    Application.Port := 8000;
    Application.Threaded := true;
    Application.Initialize;
    Application.Run;
end.
