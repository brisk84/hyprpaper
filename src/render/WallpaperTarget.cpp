#include "WallpaperTarget.hpp"

#include <chrono>
#include <hyprgraphics/image/Image.hpp>
using namespace Hyprgraphics;

CWallpaperTarget::~CWallpaperTarget() {
    ;
}

void CWallpaperTarget::create(const std::string& path) {
    m_szPath = path;

    const auto       BEGINLOAD = std::chrono::system_clock::now();

    auto loadedImage = CImage(path);
    if (!loadedImage.success()) {
        Debug::log(CRIT, "Cannot load image %s: %s", path.c_str(), loadedImage.getError().c_str());
        exit(1);
    }

    m_vSize = loadedImage.cairoSurface()->size();

    const auto MS = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - BEGINLOAD).count() / 1000.f;

    Debug::log(LOG, "Preloaded target %s in %.2fms -> Pixel size: [%i, %i]", path.c_str(), MS, (int)m_vSize.x, (int)m_vSize.y);

    m_pCairoSurface = loadedImage.cairoSurface();
}
