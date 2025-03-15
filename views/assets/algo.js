const algoDetail = {
    "partition": {
        "c": {
            "seq": "Zaporedni program",
            "mlt_stc": "Več problemov se rešuje hkrati z nastavitvijo 'schedule(static)'",
            "mlt_dyn": "Več problemov se rešuje hkrati z nastavitvijo 'schedule(dynamic)'",
            "sgl_dyn": "En problem se rešuje hkrati z nastavitvijo 'schedule(dynamic)'",
            "sgl_stc": "En problem se rešuje hkrati z nastavitvijo 'schedule(static)'",
            "nested": "Gnezdeni paralelizem - več problemov se izvaja vzporedno 'schedule(dynamic)', pri čemer se tudi vsak posamičen problem izvaja vzporedno 'schedule(static)'",
        },
        "go": {
            "seq": "Zaporedni program",
            "par": "Paralelni program",
        },
        "julia": {
            "seq": "Zaporedni program",
            "par": "Paralelni program",
        },
    },
    "kamada_kawai": {
        "c": {
            "seq": "Zaporedni program",
            "par": "Paralelni program",
            "nested": "Gnezdeni paralelizem - vzporedno se računajo tako delte kot tudi razdalje",
        },
        "go": {
            "seq": "Zaporedni program",
            "par": "Paralelni program",
        },
        "julia": {
            "seq": "Zaporedni program",
            "par": "Paralelni program",
        },
    },
}