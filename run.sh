#!/bin/bash

# 프로젝트 디렉토리 경로 가져오기
PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$PROJECT_DIR/build"

echo "🚀 Clipsmith를 실행 준비 중..."

# build 디렉토리 확인 및 생성
if [ ! -d "$BUILD_DIR" ]; then
    echo "📂 빌드 디렉토리를 생성합니다..."
    mkdir -p "$BUILD_DIR"
fi

cd "$BUILD_DIR"

# CMake 설정 및 빌드
echo "🛠️ 코드를 컴파일하고 있습니다..."
cmake .. > /dev/null
make -j$(nproc) > /dev/null

if [ $? -eq 0 ]; then
    echo "✅ 빌드 성공! Clipsmith를 실행합니다."
    ./Clipsmith
else
    echo "❌ 빌드에 실패했습니다. 코드를 확인해 주세요."
    exit 1
fi
