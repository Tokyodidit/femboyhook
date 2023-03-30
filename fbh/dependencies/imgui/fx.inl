#define min(x,y) ((x)<(y)?x:y)
#define wh() ImColor(var::menu::background_effect_color)
void FX(ImDrawList* d, ImVec2 a, ImVec2 sz, float t)
{
    for (int i = 0; i < 1777; ++i) {
        unsigned h = gui::GetID(d + i + int(t / 4));
        auto f = fmodf(t + fmodf(h / 777.f, 99), 99);
        auto tx = h % (int)sz.x;
        auto ty = h % (int)sz.y;
        if (f < 1) {
            auto py = ty - 777 * (1 - f);
            d->AddLine({ a.x + tx, a.y + py }, { a.x + tx, a.y + min(py + 10,ty) }, wh(1 - (f - 1) * 5.f));
        }
        else if (f < 1.2f)
            d->AddCircle({ a.x + tx, a.y + ty }, (f - 1) * 10 + h % 5, wh(1 - (f - 1) * 5.f));
    }
}