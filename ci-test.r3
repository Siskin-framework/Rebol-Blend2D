Rebol [
    title: "Rebol/Blend2D extension CI test"
]

;; the newly builded extension is for a test placed in current directory
insert system/options/module-paths what-dir

;; run the real test script
do %test/test.r3
