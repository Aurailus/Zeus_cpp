//
// Created by aurailus on 08/01/19.
//

#include "MainMenuScene.h"

MainMenuScene::MainMenuScene(ClientState& state) :
    Scene(state),
    sandbox(sandboxArea, state, sandboxContainer) {

    state.renderer.setClearColor(0, 0, 0);
    state.renderer.getWindow().lockMouse(false);

    Font f(state.defs.textures, state.defs.textures["font"]);
    win = state.renderer.getWindow().getSize();
    sandboxArea = win - glm::ivec2(0, 18 * GS);

    components.add(sandboxContainer);

    branding = std::make_shared<GUIContainer>("zephaBranding");
    components.add(branding);
    {
        auto zephaText = std::make_shared<GUIText>("zephaText");
        zephaText->create({GS, GS}, {}, {}, {1, 1, 1, 1}, f);
        zephaText->setText("Zepha");
        branding->add(zephaText);

        auto alphaText = std::make_shared<GUIText>("alphaText");
        alphaText->create({GS, GS}, {}, {}, {1, 0.5, 0.7, 1}, f);
        alphaText->setText("ALPHA");
        alphaText->setPos({25*GS, 0});
        branding->add(alphaText);
    }

    navigationBar = std::make_shared<GUIContainer>("navigationBar");
    navigationBar->add(std::make_shared<GUIContainer>("navigationBarBg"));
    navigationBar->add(std::make_shared<GUIContainer>("navigationBarIcons"));

    auto navigationBarIcons = navigationBar->get<GUIContainer>("navigationBarIcons");

    components.add(navigationBar);
    {
        auto settingsButton = std::make_shared<GUIImageButton>("settingsButton");
        settingsButton->create({16 * GS, 16 * GS}, {},
                               state.defs.textures["crop(0, 0, 16, 16, menu_flag_settings)"],
                               state.defs.textures["crop(16, 0, 16, 16, menu_flag_settings)"]);
        navigationBar->get<GUIContainer>("navigationBarIcons")->add(settingsButton);

        auto closeButton = std::make_shared<GUIImageButton>("closeButton");
        closeButton->create({16 * GS, 16 * GS}, {},
                            state.defs.textures["crop(0, 0, 16, 16, menu_flag_quit)"],
                            state.defs.textures["crop(16, 0, 16, 16, menu_flag_quit)"]);
        closeButton->setClickCallback([]() { exit(0); });
        navigationBar->get<GUIContainer>("navigationBarIcons")->add(closeButton);

        auto serversButton = std::make_shared<GUIImageButton>("serversButton");
        serversButton->create({16 * GS, 16 * GS}, {},
                              state.defs.textures["crop(0, 0, 16, 16, menu_flag_multiplayer)"],
                              state.defs.textures["crop(16, 0, 16, 16, menu_flag_multiplayer)"]);
        serversButton->setPos({GS, GS});
        navigationBarIcons->add(serversButton);

        auto contentButton = std::make_shared<GUIImageButton>("contentButton");
        contentButton->create({16 * GS, 16 * GS}, {},
                              state.defs.textures["crop(0, 0, 16, 16, menu_flag_content)"],
                              state.defs.textures["crop(16, 0, 16, 16, menu_flag_content)"]);
        contentButton->setPos({GS + GS * 18, GS});
        contentButton->setClickCallback([&](){ state.desiredState = "connect"; });
        navigationBarIcons->add(contentButton);

        auto divider = std::make_shared<GUIRect>("divider");
        divider->create({GS, GS * 10}, {}, {1, 1, 1, 0.3});
        divider->setPos({GS * 2 + GS * 18 * 2, GS * 4});
        navigationBarIcons->add(divider);

        findSubgames();

        for (unsigned int i = 0; i < subgames.size(); i++) {
            auto &subgame = subgames[i];
            auto button = std::make_shared<GUIImageButton>(subgame.config.name);
            button->create({16 * GS, 16 * GS}, {},
                           state.defs.textures["crop(0, 0, 16, 16, " + subgame.iconRef->name + ")"],
                           state.defs.textures["crop(16, 0, 16, 16, " + subgame.iconRef->name + ")"]);
            button->setPos({GS * 7 + GS * 18 * (i + 2), GS});
            button->setClickCallback([&, i]() {
                selectedSubgame = &subgame;
                sandbox.load(selectedSubgame->subgamePath);
            });
            navigationBarIcons->add(button);
        }
    }

    if (subgames.size() > 0) {
        selectedSubgame = &subgames[0];
        sandbox.load(selectedSubgame->subgamePath);
    }

    positionElements();
}

void MainMenuScene::findSubgames() {
    std::string subgamesPath = state.path + "subgames";

    cf_dir_t subgamesDir;
    cf_dir_open(&subgamesDir, subgamesPath.data());
    while (subgamesDir.has_next) {
        cf_file_t subgameFolder;
        cf_read_file(&subgamesDir, &subgameFolder);
        if (!subgameFolder.is_dir) { cf_dir_next(&subgamesDir); continue; }

        bool hasConf = false;
        bool hasIcon = false;

        cf_dir_t subgame;
        cf_dir_open(&subgame, subgameFolder.path);
        while (subgame.has_next) {
            cf_file_t file;
            cf_read_file(&subgame, &file);

            if (!file.is_dir && strncmp(file.name, "icon.png", 8) == 0) hasIcon = true;
            if (!file.is_dir && strncmp(file.name, "conf.json", 9) == 0) hasConf = true;

            cf_dir_next(&subgame);
        }
        cf_dir_close(&subgame);

        if (!hasConf || !hasIcon) { cf_dir_next(&subgamesDir); continue; }

        json j {};
        std::ifstream i(std::string(subgameFolder.path) + "/conf.json");
        i >> j;

        std::string name = j["name"];
        std::string description = j["description"];
        std::string version = j["version"];

        subgames.push_back({
           state.defs.textures.loadImage(std::string(subgameFolder.path) + "/icon.png", name),
           {name, description, version}, subgameFolder.path
        });

        cf_dir_next(&subgamesDir);
    }
    cf_dir_close(&subgamesDir);

    std::sort(subgames.begin(), subgames.end(), [](Subgame& a, Subgame& b) {
        return a.config.name < b.config.name;
    });
}

void MainMenuScene::positionElements() {
    sandbox.windowResized();

    branding->setPos({win.x - 55*GS, win.y - 30*GS});

    navigationBar->setPos({0, win.y - 18*GS});

    auto navigationBarBg = navigationBar->get<GUIContainer>("navigationBarBg");
    for (unsigned int i = 0; i < static_cast<float>(win.x) / 64.f / GS; i++) {
        auto segment = std::make_shared<GUIRect>("segment_" + to_string(i));
        segment->create({64 * GS, 18 * GS}, {}, state.defs.textures["menu_bar_bg"]);
        segment->setPos({i * 64 * GS, 0});
        navigationBarBg->add(segment);
    }

    auto navigationBarIcons = navigationBar->get<GUIContainer>("navigationBarIcons");
    navigationBarIcons->get<GUIImageButton>("closeButton")->setPos({win.x - 16*GS - GS, GS});
    navigationBarIcons->get<GUIImageButton>("settingsButton")->setPos({win.x - 16*GS*2 - GS*3, GS});
}

void MainMenuScene::update() {
    state.defs.textures.update();
    sandbox.update(state.deltaTime);

    if (state.renderer.resized) {
        win = state.renderer.getWindow().getSize();
        sandboxArea = win - glm::ivec2(0, 18 * GS);
        positionElements();
        state.renderer.resized = false;
    }

    components.mouseActivity(state.renderer.getWindow().getMousePos());
    if (state.renderer.getWindow().input.isMousePressed(GLFW_MOUSE_BUTTON_LEFT)) {
        components.triggerClick(state.renderer.getWindow().getMousePos());
    }
}

void MainMenuScene::draw() {
    state.renderer.beginChunkDeferredCalls();
    state.renderer.endDeferredCalls();

    state.renderer.beginGUIDrawCalls();
    state.renderer.enableTexture(&state.defs.textures.atlasTexture);
    components.draw(state.renderer);
    state.renderer.swapBuffers();
}