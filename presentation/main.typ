#import "@preview/touying:0.6.1": *
#import "fonts.typ": *
#import themes.simple: *
#import "@preview/fletcher:0.5.8" as fletcher: node, edge

#let fletcher-diagram = touying-reducer.with(reduce: fletcher.diagram, cover: fletcher.hide)

#set raw(theme: "gruvbox.tmTheme")

#show: simple-theme.with(
  aspect-ratio: "16-9",
  header: none,
  footer: none,
  footer-right: none,
  config-page(
    margin: (top: 1.5em, bottom: 1.5em),
    fill: bg0,
  ),
  config-common(
    // show-notes-on-second-screen: bottom,
    // handout: true,
  )
)

#set text(size: 25pt, font: "CommitMonoKapucni", fill: fg1)

#show heading: it => block(below: 0.75em, above: 0em)[
  #set text(size: 42pt)
  #it
]

#show quote: it => text(fill: fg4, style: "italic", weight: "light", it.body)

#set list(
  marker: [#tgray[>]],
  spacing: 1em
)

#show raw: it => block(
  stroke: gray,
  width: 100%,
  inset: 1em,
  it
)

#show link: it => underline(
  text(
    fill: blue,
    it
  )
)

#slide[
  #set align(horizon)
  = #taqua[printf]

  #small[
    #quote[
      dokumentumok nyomtatását optimalizáló szoftver
    ]
  ]

  kovács bálint

  \2026. \06. \24.

]

#slide[
  = #tblue[előzmények]

  #pause

  #place(
    bottom,
    image("img/plotter.png", width: 45%),
  )

  #pause

  #place(
    right,
    image("img/script_showcase.png", height: 80%),
  )

  #place(
    bottom + right,
    image("img/ps.svg", width: 10%),
    dy: +0.5em,
    dx: +0.5em,
  )
]

// single
#slide[
  = #tgreen[felesleg minimalizálás]

  #pause
  - egyetlen méret esetén viszonylag egyszerű

  // TODO: ábra
]

// multi
#slide[
  = #tgreen[felesleg minimalizálás]

  - több méret esetén nem triviális
  #pause
  - ládapakolás #pause #tgray[(np nehéz)]
  #pause
  - _vágóasztallal vágható_ ládapakolás #pause #tgray[(np nehéz)]
  // TODO: vágóasztallal vághatóság pic
]

// heur
#slide[
  = #tgreen[felesleg minimalizálás]

  - heurisztikus megoldás létezik
  - sorbarendezés
  - csíkonként elhelyezzük a legnagyobbat
  - keletkező csíkokat rekurzívan kitöltjük
]

#slide[
  = #torange[technológiák]

  #pause
  #place(
    horizon + left,
    image("img/cpp.svg", width: 20%),
  )

  #pause
  #place(
    horizon + center,
    image("img/opencv.svg", width: 20%),
  )

  #pause
  #place(
    horizon + right,
    image("img/qt.svg", width: 20%),
  )
]

#slide[
  = #tpurple_dim[fordítás]
  
  #pause
  #place(
    horizon + left,
    image("img/codeblocks.png", width: 20%),
  )

  #pause
  #place(
    horizon + center,
    image("img/cmake.svg", width: 20%),
  )

  #pause
  #place(
    horizon + right,
    image("img/meson_dim.svg", width: 20%),
  )
]

#slide[
  = #tpurple_dim[fordítás]

  #place(
    bottom + right,
    image("img/qt.svg", width: 10%),
    dy: -0.5em,
  )

  - qml, _js_
  #pause
  - c++ qt makrók
  #pause
  - preprocesszálni kell
  #pause
  - meson qt6 modul
]

#slide[
  = #torange[fejlesztés]

  #place(
    bottom + right,
    image("img/cpp.svg", width: 10%),
    dy: -0.5em,
  )
  #pause
  - c++-23 nyelvi elemek
  #pause
  - \"lassú\" generálás külön szálon
  #pause
  - perzisztens lusta lista
]

#slide[
  = #tblue[eredmények]

  // TODO: ui pic
  // TODO: strip tiled example
]

#slide[
  = #tyellow[értékelés]

  #pause
  - pozitív felhasználói visszajelzések
  #pause
  #place(
    center,
    image("img/plot_psvs_dark.png", height: 70%),
    dy: +0.5em,
  )
]

#focus-slide(
  background: aqua,
  foreground: bg0
)[
  = kérdések
]

#slide[
  #set align(horizon)
  #quote[
    Miért volt szükség az OpenCV könyvtárra a képek manipulálásához, mire nem nyújtott megoldást a program többi részében használt Qt saját funkcionalitása (pl. QImage osztály)?
  ]
]

#slide[
  = miért #tblue[opencv] (és nem #tgreen[qt])?

  #place(
    bottom + right,
    image("img/opencv.svg", width: 10%),
  )
  #pause
  - alacsony szintű hozzáférés
  #pause
  - mátrix reprezentáció és műveletek
  #pause
  - beépített átméretezési algoritmusok
  #pause
  - beépített rajzolási műveletek
]

#slide[
  #set align(horizon)
  #quote[
    Az 5.4.2. szakaszban azt írja, hogy a PDF formátumú fájlokat "betöltéskor a megfelelő pixelsűrűség mellett raszterizálni kell." Hogy határozza meg az említett pixelsűrűséget, figyelembe veszi az alkalmazott filtereket (pl. átméretezés)?
  ]
]

#slide[
  = pdf-ek #torange[raszterizálása]

  #pause
  - _vektorgrafikus_ formátum, raszterizálni kell
  #pause
  - mi a méret pixelben?
  #pause
  - adott valós méret és pixelsűrűség
  #pause
  $ s_(p x) = s_(m m) dot text("dpi") / 0.0254 $ 
  
  // TODO: ábra
]

#slide[
  EOF
]