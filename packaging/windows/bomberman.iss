; Inno Setup script for the Windows installer.
; Build: iscc /DAppVersion=1.0 /DSourceDir=<cmake --install prefix> packaging\windows\bomberman.iss

#ifndef AppVersion
  #define AppVersion "0.0.0-dev"
#endif
#ifndef SourceDir
  #define SourceDir "..\..\dist\bomberman"
#endif

[Setup]
AppId={{5C0E6A3B-7B8E-4E0F-9C4B-2D9B1E5A7F31}
AppName=Bomberman
AppVersion={#AppVersion}
AppPublisher=Kitero
AppPublisherURL=https://github.com/Kitero/bomberman_IrrLicht
DefaultDirName={autopf}\Bomberman
DefaultGroupName=Bomberman
DisableProgramGroupPage=yes
OutputBaseFilename=bomberman-windows-x64-setup
ArchitecturesAllowed=x64compatible
ArchitecturesInstallIn64BitMode=x64compatible
PrivilegesRequiredOverridesAllowed=dialog
UninstallDisplayIcon={app}\bomberman.exe
Compression=lzma2
SolidCompression=yes
WizardStyle=modern

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "french"; MessagesFile: "compiler:Languages\French.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "{#SourceDir}\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs

; The game loads its data relative to the working directory
[Icons]
Name: "{group}\Bomberman"; Filename: "{app}\bomberman.exe"; WorkingDir: "{app}"
Name: "{group}\{cm:UninstallProgram,Bomberman}"; Filename: "{uninstallexe}"
Name: "{autodesktop}\Bomberman"; Filename: "{app}\bomberman.exe"; WorkingDir: "{app}"; Tasks: desktopicon

[Run]
Filename: "{app}\bomberman.exe"; WorkingDir: "{app}"; Description: "{cm:LaunchProgram,Bomberman}"; Flags: nowait postinstall skipifsilent
