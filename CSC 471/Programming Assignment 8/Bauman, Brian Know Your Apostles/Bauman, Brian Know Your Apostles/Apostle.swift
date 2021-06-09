//
//  Apostles.swift
//  Bauman, Brian Know Your Apostles
//
//  Created by Brian Bauman on 3/11/19.
//  Copyright © 2019 Brian Bauman. All rights reserved.
//

import Foundation

let apostles = [
    Apostle(name: "Simon",
            nickname: "Namechanger the Gamechanger",
            funFact: "Founded a long tradition of name changing. Chad Ochocinco, The Artist Formerly Known As Prince,  etc. all revere him as a visionary.",
            description: "Simon the Apostle was truly an outcast in his time. Born in 35 BC, he was raised by a skilled blacksmith and, by the age of 10, he crafted his first broadsword of hardened steel. He was thoroughly bullied for his dedication to weaponry in place of the Church. Embarrassed, he decided to change his name to something entirely different than Simon. He chose Peter. At age 20, he passed from this world, leaving his wife and six children fatherless.",
            imageName: "simon"),

    Apostle(name: "Andrew",
            nickname: "Huckleberry Fin-hands",
            funFact: "Was born with webbed fingers and toes, but had them surgically separated. Later regretted the surgery after realizing he could no longer use his hands as a fishing net.",
            description: "A childhood deformity led the apostle Andrew to become a great fisherman. His name, literally translated from Greek to mean 'fin-hands', memorializes his condition -- both a blessing and a curse. After years of hunting the great game of the sea, he settled down with his wife, Deborah, who he met on Christian Mingle.",
            imageName: "andrew"),
    
    Apostle(name: "James",
            nickname: "James 1",
            funFact: "While hotly debated amongst historians, it's generally agreed upon that LeBron James was named after him.",
            description: "James often referred to himself as \"James the Greater\" and was mostly concerned with getting other people to agree with this designation. In order to distinguish himself from another apostle with the same first name, he wore platform shoes regularly, exclaiming, \"Look at this little guy! I am much greater! Right?\". The apostle Thaddeus is quoted as saying  \"Jesus loved neither James, really. They were both pretty annoying.\"",
            imageName: "james"),
    
    Apostle(name: "John",
            nickname: "The Not-Baptist",
            funFact: "Gets mistaken for John the Baptist so regularly that he actually took swimming lessons.",
            description: "The apostle John never knew his parents and was delivered to his adoptive parents by a strong gust of late-Autumn wind. Seeing this as a sign from God, they took him in and nurtured him to full health. It became clear after a few years that John was different. He took a liking to secluded places and constantly drew what could only be described as \"Renaissance nudes\". After joining the posse, he began to visually chronicle the hither-tos and where-fors of Apostolic life. This later became the Graphic Gospel of John and is largely regarded as \"pretty cool\".",
            imageName: "john"),
    
    Apostle(name: "Thaddeus",
            nickname: "Raddeus",
            funFact: "Crushed 30 beers in less than two hours once, according to Uncle Bart",
            description: "Arguably the first fraternity, the 12 Apostles found their stereotypical energetic meathead in the apostle Thaddeus. Weeks blurred together as he charged forward in a continuous bender, living to party and partying to live. One of the few to witness Jesus' transformation of water into wine, Thaddeus praised the thought but chided the result, claiming wine is for \"girls\". Though most modern manuscripts ignore this fact, he was commonly known as \"Raddeus\" by his close friends, particularly when drunk.",
            imageName: "thaddeus"),
    
    Apostle(name: "Bartholomew",
            nickname: "Uncle Bart",
            funFact: "The singular witness to Raddeus' beer-acle.",
            description: "Little is known about the apostle Bartholomew, other than what can be pieced together from a collection of first-hand accounts recorded by his twin sister, Jennifer. She claims he was always drawn to nature -- the moon in particular. Later in life, he was depicted holding a knife and his own skin. \"That's metal\", his sister noted.",
            imageName: "bartholomew"),
    
    Apostle(name: "Thomas",
            nickname: "Doubting Thomas",
            funFact: "Still doesn't believe in a spherical Earth, even after Jesus spent two hours laying out the evidence.",
            description: "After a dark, tumultuous four years at college doubting his own existence (triggered by a rather intense exposure to DMT, a hallucinogenic chemical), Thomas had troubling believing anything. When he met Jesus -- and was able to truly believe for the first time in years -- he rejoiced. Interviews with Thomas later in his life quote him as saying, \"That never happened.\", directly doubting his recorded lack of doubt.",
            imageName: "thomas"),
    
    Apostle(name: "James",
            nickname: "James 2",
            funFact: "Barely even an apostle. Was only included in the group chat when someone added the wrong James from their contacts.",
            description: "Little is known about James the Apostle. In the late 19th century, archaeologists near modern-day Syria uncovered a relic containing large swaths of an iMessage conversation between the apostles. It seems, based on the chat history, that James 2 was actually added to the group before James 1. However, it seems to have been a mistake -- Jesus selected the wrong contact and wasn't sure how to politely remove him. So, he remained.",
            imageName: "james2"),
    
    Apostle(name: "Matthew",
            nickname: "The Silver Fox",
            funFact: "His nickname has nothing to do with how good he looks with gray hair.",
            description: "Matthew first gained international acclaim as the first novelist to release a triple-platinum book, his self-named magnum opus, \"The Book of Matthew\". While book tours and speakings hogged a large majority of his time during Jesus' last days, he always made up for it by making sure his apostles got free, front row tickets when he was touring in their city. Peter claims to have been refused entrance when Will Call only had tickets for \"Simon\", but this is unconfirmed.",
            imageName: "matthew"),
    
    Apostle(name: "Philip",
            nickname: "Metalhead",
            funFact: "After being inspired by God's Word, built the first 12-string guitar.",
            description: "A close fried of Simon The Unknown, Philip was a trusted companion, a devout believer in the metric system of measurement, and an avant-garde death metal guitarist. \"Metalhead\" to his friends, he spent the majority of his days working on advanced, mathematical chord progressions and appregiated melodies. His first Top 100 hit, \"Drain Judas of All Blood, Dear Lord\", saw limited success after its 33 AD release, prominently amongst the remaining Apostles.",
            imageName: "philip"),
    
    Apostle(name: "Simon",
            nickname: "The Unknown",
            funFact: "Simon was the Christian world's first and foremost Fugees fan.",
            description: "A minor player in the story of Jesus and the Apostles, Simon played a lead role in his own, smaller circles. Namely, the Gethsemane Fugees Super Fan Club, of which he was the founding member. Surprisingly, this group also housed 12 members, all from different walks of life, all sharing one true passion. Often, modern pastors will wax poetic regarding Simon the Unknown, warning of splitting your time between Jesus and your vices. \"Lest ye be never known!\", etc.",
            imageName: "simon2"),
    
    Apostle(name: "Judas Iscariot",
            nickname: "That Guy",
            funFact: "Accidentally traded his best bud's life for a bitcoin wallet, but lost the password.",
            description: "A champion of LGBT rights, Judas took advantage of his celebrity status to prove, in full view of a legion of Roman guards, that there was nothing wrong with a man kissing another man. To motivate the point, he chose the manliest friend he had -- Jesus. Unfortunately, the Romans disagreed and sentenced Jesus to death for this heinous crime.",
            imageName: "judas"),
]

class Apostle {
    var name: String
    var nickname: String
    var funFact: String
    var description: String
    var imageName: String
    
    init(name: String,
         nickname: String,
         funFact: String,
         description: String,
         imageName: String) {
        self.name = name
        self.nickname = nickname
        self.funFact = funFact
        self.description = description
        self.imageName = imageName
    }
}
