# structure

## bevezetés, előzmények

- kollégiumi nyomda
- plotter
    - tekercsre nyomtatunk
    - van ehhez canon szoftver csak szar
- ezért van egy ps script
    - már egyszer refaktoráltam
    - nehezen bővíthető, limitált, lassú, nem optimális
- ezért döntöttem úgy hogy lefejlesztem a printfet ami ezekre megoldást nyújtana

## hogyan minimalizálunk felesleget

- 2 eset
- 1 féle dokumentumot nyomtatunk
    - kitöltött és nem kitöltött sorok, mikor mi az optimális
- több féle dokumentumot nyomtatunk
    - bin packing? np nehéz
    - bin packing extra megkötésekkel? az is np nehéz
        - a megkötés
    - közelítő heurisztikus megoldás viszont van
    - heurisztika alapján szortírozunk
    - lelhelyezünk egyet, és a maradék helyre (na de hogyan) rekurzívan folytatjuk azzal ami oda fér
    - na de milyen heurisztika?
        - statok

## stack

- elsődleges szempont: sebesség
    - a ps script legnagyobb hibája hogy túl high level
    - cpp mert low level managelhetjük a memóriát
    - qt mert cross platform, és személyes bias mert linux és meg akartam tanulni
    - openvc mert idk yet

## buildelés

- codeblocks
- konkrétan nincs tárgy ahol lenne szó cpp fordításról like come the fuck on
- cmake elsőre lehet hogy nem triviális
- meson
    - glaze
- qt preprocessing és a qt dolgok buildelésének menete pontosan

## fejlesztés

- többnyire problémák nélkül
- képgenerálás gyors de nem eléggé
    - külön szálon futás
- lazy lista? could be cut content idrc

## benchmark

- nem mérvadó mert debugban fordítottam, azóta jobb
- jó visszajelzések
- még nincs wiki de triviális használni

## kérdések

- miért opencv QImage helyett
    - hülye kérdés
- hogyan határozza meg a pixelsűrűséget, figyelembe veszi e az átméretezést
    - hülye kérdés