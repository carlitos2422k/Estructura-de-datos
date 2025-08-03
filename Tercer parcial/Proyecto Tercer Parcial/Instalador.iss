[Setup]
AppName=MiPrograma
AppVersion=1.0
DefaultDirName=C:\Users\Carlos\Desktop\Estructura de datos\Tercer parcial\Proyecto Tercer Parcial
DisableDirPage=yes
DefaultGroupName=MiPrograma
OutputBaseFilename=MiProgramaInstaller
Compression=lzma
SolidCompression=yes
CreateAppDir=no

[Files]
; No incluimos archivos porque queremos usar el ejecutable que ya está en la ubicación

[Dirs]
; Asegurarse de que la carpeta existe (no debería ser necesario pero por si acaso)
Name: "C:\Users\Carlos\Desktop\Estructura de datos\Tercer parcial\Proyecto Tercer Parcial"; Flags: uninsneveruninstall

[Icons]
; Crear acceso directo que apunte directamente a la ubicación exacta
Name: "{group}\MiPrograma"; Filename: "C:\Users\Carlos\Desktop\Estructura de datos\Tercer parcial\Proyecto Tercer Parcial\main.exe"; WorkingDir: "C:\Users\Carlos\Desktop\Estructura de datos\Tercer parcial\Proyecto Tercer Parcial"

[Code]
var
  InputPage: TInputQueryWizardPage;
  UserKey: String;
procedure InitializeWizard();
begin
  InputPage := CreateInputQueryPage(wpWelcome, 
    'Clave de Instalación', 
    'Introduce tu clave de instalación para continuar', 
    'Ingresa la clave de instalación en el campo de texto a continuación:');
  InputPage.Add('Clave de Instalación:', False);
end;
function NextButtonClick(CurPageID: Integer): Boolean;
begin
  Result := True;
  if CurPageID = InputPage.ID then
  begin
    UserKey := InputPage.Values[0];
    if UserKey = '' then
    begin
      MsgBox('Debes ingresar una clave para continuar.', mbError, MB_OK);
      Result := False;
    end
    else if UserKey <> 'ABC12-ASD12-TPOP8-POPA9-89ASD' then
    begin
      MsgBox('Clave inválida. Instalación cancelada.', mbError, MB_OK);
      Result := False;
    end;
  end;
end;