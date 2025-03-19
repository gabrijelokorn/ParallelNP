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
            "mlt_all_chn": "Vsak partition problem je dinamično dodeljen svoji goroutine-i. Goroutine-i so sinhronizirani z uporabo kanalov",
            "mlt_dyn_chn": "Dinamično porazdeljevanje dela med goroutine - z uporabo kanalov. Goroutine-i so sinhronizirani z uporabo kanalov",
            "mlt_all": "Vsak partition problem je dinamično dodeljen svoji goroutine-i.",
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