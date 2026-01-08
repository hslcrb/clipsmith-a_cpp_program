#!/bin/bash
# make_deb.sh - Clipsmith v1.0 원클릭 .deb 패키지 생성 및 설치 스크립트
# (One-click .deb package creator and installer for Clipsmith)

PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$PROJECT_DIR/build"
VERSION="1.0.0"
PKG_NAME="clipsmith_${VERSION}_amd64"
ROOT_DIR="$PROJECT_DIR/$PKG_NAME"

echo "📦 Clipsmith .deb 패키지 생성을 시작합니다..."

# 1. 최신 코드 빌드
if [ ! -d "$BUILD_DIR" ]; then mkdir -p "$BUILD_DIR"; fi
cd "$BUILD_DIR"
cmake .. > /dev/null
make -j$(nproc) > /dev/null

if [ $? -ne 0 ]; then
    echo "❌ 빌드에 실패했습니다. 코드를 확인해 주세요."
    exit 1
fi

# 2. 패키지 구조 생성
echo "📂 패키지 구조를 구성하는 중..."
cd "$PROJECT_DIR"
rm -rf "$PKG_NAME"
mkdir -p "$PKG_NAME/usr/bin"
mkdir -p "$PKG_NAME/usr/share/applications"
mkdir -p "$PKG_NAME/usr/share/icons/hicolor/256x256/apps"
mkdir -p "$PKG_NAME/DEBIAN"

# 3. 파일 복사
cp "$BUILD_DIR/Clipsmith" "$PKG_NAME/usr/bin/clipsmith"
cp "$PROJECT_DIR/resources/logo.png" "$PKG_NAME/usr/share/icons/hicolor/256x256/apps/clipsmith.png"

# 4. .desktop 파일 생성
cat <<EOF > "$PKG_NAME/usr/share/applications/clipsmith.desktop"
[Desktop Entry]
Name=Clipsmith
Comment=Smart Clipboard Manager (Gemini AI Enhanced)
Exec=/usr/bin/clipsmith
Icon=clipsmith
Terminal=false
Type=Application
Categories=Utility;
StartupNotify=true
EOF

# 5. 제어(control) 파일 생성
cat <<EOF > "$PKG_NAME/DEBIAN/control"
Package: clipsmith
Version: ${VERSION}
Section: utils
Priority: optional
Architecture: amd64
Depends: qt6-base-dev, libqt6sql6-sqlite
Maintainer: Rheehose (Rhee Creative) & Gemini 3 Flash
Description: High-end smart clipboard manager for Linux.
 Features Glassmorphism & Frutiger Aero aesthetics. 
 Collaboratively developed by Rheehose and Gemini 3 Flash.
EOF

# 6. 패키지 빌드
echo "🛠️ .deb 파일을 생성하는 중..."
chmod -R 755 "$PKG_NAME"
dpkg-deb --build "$PKG_NAME" > /dev/null

if [ $? -eq 0 ]; then
    echo "✅ 패키지 생성 성공: ${PKG_NAME}.deb"
    rm -rf "$PKG_NAME"
    
    # 7. 즉시 설치 및 실행 여부 확인
    echo "--------------------------------------------------"
    read -p "🚀 지금 바로 패키지를 설치하고 실행하시겠습니까? (y/n): " choice
    if [[ "$choice" == "y" || "$choice" == "Y" ]]; then
        echo "🔧 패키지를 설치합니다 (sudo 권한 필요)..."
        sudo dpkg -i "${PKG_NAME}.deb"
        sudo apt-get install -f -y > /dev/null # 미설치 의존성 해결
        
        echo "🏃 Clipsmith를 실행합니다!"
        clipsmith &
    fi
else
    echo "❌ 패키지 생성에 실패했습니다."
    exit 1
fi
