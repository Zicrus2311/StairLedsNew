#include "hsvRgb.h"

#include <Arduino.h>

#include "FastLED.h"

float hsvRgb::fract(float x) { return x - int(x); }

float hsvRgb::mix(float a, float b, float t) { return a + (b - a) * t; }

float hsvRgb::step(float e, float x) { return x < e ? 0.0 : 1.0; }

CRGB hsvRgb::hsv2rgb(CHSV color) {
    float h = color.h / 255.0f, s = color.s / 255.0f, b = color.v / 255.0f;

    float resultR = b * mix(1.0, constrain(abs(fract(h + 1.0) * 6.0 - 3.0) - 1.0, 0.0, 1.0), s);
    float resultG = b * mix(1.0, constrain(abs(fract(h + 0.6666666) * 6.0 - 3.0) - 1.0, 0.0, 1.0), s);
    float resultB = b * mix(1.0, constrain(abs(fract(h + 0.3333333) * 6.0 - 3.0) - 1.0, 0.0, 1.0), s);
    return CRGB(resultR * 255, resultG * 255, resultB * 255);
}

CHSV hsvRgb::rgb2hsv(CRGB color) {
    float r = color.r / 255.0f, g = color.g / 255.0f, b = color.b / 255.0f;

    float s = step(b, g);
    float px = mix(b, g, s);
    float py = mix(g, b, s);
    float pz = mix(-1.0, 0.0, s);
    float pw = mix(0.6666666, -0.3333333, s);
    s = step(px, r);
    float qx = mix(px, r, s);
    float qz = mix(pw, pz, s);
    float qw = mix(r, px, s);
    float d = qx - min(qw, py);
    float resultH = abs(qz + (qw - py) / (6.0 * d + 1e-10));
    float resultS = d / (qx + 1e-10);
    float resultV = qx;
    return CHSV(resultH * 255, resultS * 255, resultV * 255);
}

CRGB hsvRgb::q_hue2rgb(byte hue) {
    float resultR = constrain(abs((byte)hue * (int)6 - 765) - 255, 0, 255);
    float resultG = constrain(abs((byte)(hue + 171) * (int)6 - 765) - 255, 0, 255);
    float resultB = constrain(abs((byte)(hue + 85) * (int)6 - 765) - 255, 0, 255);
    return CRGB(resultR, resultG, resultB);
}