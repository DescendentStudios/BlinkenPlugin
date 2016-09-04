# Blinken
Unreal Engine 4 (UE4) plugin to control accessory lighting (Razer Chroma, Alienware AlienFX, Logitech G)

# Licenses

See the LICENSE file for license for all files, except for files in the ThirdParty directory which are covered by other licenses:
* Razer Chroma SDK covered by license at http://developer.razerzone.com/chroma/
* Alienwave AlienFX SDK covered by license at http://www.alienware.com/landings/alienfx/
* Logitech G LED Illumunation SDK covered by license at http://gaming.logitech.com/en-us/developers

# Usage

1. Add the plugin to your project (by putting it into a Blinken directory inside your project's Plugins directory)
2. Enable the plugin in your project inside of UE4Editor
3. Use the Blueprint functions to control accessory lighting

# Blueprint functions

## Blinken BP Library

1. void UBlinkenBPLibrary::Enable(bool value)
   * Enable or disable Blinken lighting.  Defaults to enabled.
2. bool UBlinkenBPLibrary::IsEnabled()
   * Returns if Blinken effects enabled or disabled
3. void UBlinkenBPLibrary::SetGlobalColor(FColor color)
   * Sets all accessory lighting to FColor color (RGB) and assigns the color as the global color
4. void UBlinkenBPLibrary::FlashColor(FColor color, float duration)
   * Flashes FColor color on all accessory lighting for duration seconds, and returns to the global color set via SetGlobalColor() afterward

# TODO

1. Set colors on individual devices independently
2. Set individual key lighting on devices which support it, perhaps with layers where removing layer X lighting will return the keys to the previous layer's colors
3. Allow access to vendor SDK specific features - perhaps via interfaces obtainable that map directly to each SDK 
4. Add support for more hardware via more SDKs.  Examples:
   1. Roccat TalkFX (tho it seems to also support AlienFX): http://www.roccat.org/en-US/Products/Gaming-Software/Talk-FX/
   2. Corsair CUE: http://www.corsair.com/en-us/support/downloads

