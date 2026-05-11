#include <hex/plugin.hpp>
#include <hex/api/imhex_api/hex_editor.hpp>

IMHEX_PLUGIN_SETUP("Colored Bytes", "Neptuwunium", "Colors hex bytes based on nybble") {
    hex::ImHexApi::HexEditor::addForegroundHighlightingProvider([](u64, const u8 *buffer, const size_t size, const bool hasHighlight) -> std::optional<color_t> {
        if (hasHighlight || size < 1) {
            return std::nullopt;
        }

        static color_t OX00 = IM_COL32(0x80, 0x80, 0x80, 0xff);
        static color_t OXFF = IM_COL32(0xff, 0xff, 0xff, 0xff);
        static color_t colors[0x10] = {
            IM_COL32(0xe9, 0x5c, 0x91, 0xff),
            IM_COL32(0xef, 0x5e, 0x5f, 0xff),
            IM_COL32(0xe9, 0x6c, 0x00, 0xff),
            IM_COL32(0xda, 0x7a, 0x00, 0xff),
            IM_COL32(0xcb, 0x85, 0x00, 0xff),
            IM_COL32(0xa8, 0x98, 0x00, 0xff),
            IM_COL32(0x6f, 0xa9, 0x01, 0xff),
            IM_COL32(0x47, 0xaf, 0x3e, 0xff),
            IM_COL32(0x14, 0xb2, 0x54, 0xff),
            IM_COL32(0x00, 0xb4, 0x76, 0xff),
            IM_COL32(0x00, 0xb0, 0x9f, 0xff),
            IM_COL32(0x00, 0xab, 0xc1, 0xff),
            IM_COL32(0x00, 0xa4, 0xe6, 0xff),
            IM_COL32(0x36, 0x96, 0xff, 0xff),
            IM_COL32(0x9d, 0x7a, 0xf7, 0xff),
            IM_COL32(0xce, 0x67, 0xcc, 0xff),
        };

        const auto byte = buffer[0];
        if (byte == 0) {
            return OX00;
        }

        if (byte == 0xff) {
            return OXFF;
        }

        const auto nibble = byte >> 4;
        return colors[nibble];
    });
}
