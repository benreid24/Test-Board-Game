#include "Grid.hpp"
#include "Tray.hpp"
#include <BLIB/Engine.hpp>
#include <BLIB/Logging.hpp>
#include <BLIB/Media/Shapes.hpp>
#include <Properties.hpp>
#include <SFML/Graphics.hpp>

class DemoEngineState : public bl::engine::State {
public:
    static bl::engine::State::Ptr create() { return Ptr(new DemoEngineState()); }

    virtual const char* name() const { return "DemoEngineState"; }

    virtual void activate(bl::engine::Engine&) override {
        BL_LOG_INFO << "DemoEngineState activated";
    }

    virtual void deactivate(bl::engine::Engine&) override {}

    virtual void update(bl::engine::Engine&, float) override { tray.update(); }

    virtual void render(bl::engine::Engine& engine, float) override {
        engine.window().clear();
        grid.render(engine.window(), tray.get());
        tray.render(engine.window());
        engine.window().display();
    }

private:
    Tray tray;
    Grid grid;

    DemoEngineState() = default;
};

int main() {
    BL_LOG_INFO << "Loading application properties";
    if (!Properties::load()) {
        BL_LOG_ERROR << "Failed to load application properties";
        return 1;
    }

    BL_LOG_INFO << "Creating engine instance";
    const bl::engine::Settings engineSettings =
        bl::engine::Settings()
            .withVideoMode(sf::VideoMode(1000, 800, 32))
            .withWindowStyle(sf::Style::Close | sf::Style::Titlebar)
            .withWindowTitle("Game Concept");
    bl::engine::Engine engine(engineSettings);
    BL_LOG_INFO << "Created engine";

    BL_LOG_INFO << "Running engine main loop";
    if (!engine.run(DemoEngineState::create())) {
        BL_LOG_ERROR << "Engine exited with error";
        return 1;
    }

    BL_LOG_INFO << "Exiting normally";
    return 0;
}
